# Block-chain Framework
## Table of content
1. [Overview](#section_overview)
2. [Installation](#section_installation)
3. [How to create a new block-chain](#section_create)
    1. [Node](#section_node)
    2. [Config](#section_config)
    3. [Transaction](#section_transaction)
        1. [Useful methods](#sub_section_useful)
        2. [Serialization methods](#sub_section_serialization)
        3. [UI methods](#sub_section_ui)
        4. [Database methods](#sub_section_database)
    4. [Reward](#section_reward)
    5. [TransactionManager](#section_transactionManager)
    6. [Serializer](#section_serializer)
    7. [Proof](#section_proof)
        1. [New proof](#sub_section_newproof)
        2. [Feed the framework](#sub_section_feedframework)
        3. [New metadata](#sub_section_newmetadata)
    8. [Database](#section_database)
    9. [Framework](#section_framework)
4. [TODO-List](#section_todo)
    1. [Hash](#sub_section_hash)
    2. [Cryptography](#sub_section_cryptography)
    3. [Proof](#sub_section_proof)
    4. [Header files](#sub_section_header)




## Overview <a name="section_overview"></a>
This project is a C++ Framework built to allow easy and fast development of any kind of block-chain. <br/>
The idea is to limit the development to transactions and data representation only. No need to implement anything else. <br/>
Of course, as a framework, it provides a big flexibility, therefore, it is possible to write advanced block-chain by configuring as many things as you want. <br/>
> Note that everything can change to allow more flexibility.

## Installation <a name="section_installation"></a>
To install the framework, you just have to copy/paste the folder ```block_chain``` in your project's root folder

## How to create a new block-chain <a name="section_create"></a>
To create your own block-chain program, you just have to run the main objects provided by the framework.
### Node <a name="section_node"></a>
The node is the peer itself. You only have to create it and it will run.
```cpp
Node node(config);
```
### Config <a name="section_config"></a>
The node is the peer itself. You only have to create it and it will run.
```cpp
Config config("configuration file path", serializer, Proof::WORK, reward);
```
The file itself is a json file. <br/>

<h6>Example:</h6>
```json
{
  "port": 3423,
  "encoding": "json",
  "debug": true
}
```
the parameters serializer, proof and reward are explained later.
### Transaction <a name="section_transaction"></a>
Transactions are the most important thing to implement. <br/>
```cpp
#include "./block_chain/chain/block/transaction/Transaction.h"
```
There is already a pure abstract class to implement, so you basicaly just have to fill the methods for your own Transaction class.
<h4>Useful methods <a name="sub_section_useful"></a></h4>
<h5>Transaction::get_type</h5>
```cpp
int get_type() const override;
```
This method is used to give a type to a transaction. Each transaction type must have a different type. It is used as an ID.
<h6>Example:</h6>
```cpp
int MoneyTransaction::get_type() const {
    return 2;
}
```
<h5>Transaction::operator==</h5>
```cpp
bool operator==(Transaction* t) const override
```
This method is used to check if two transactions are the same
<h6>Example:</h6>
```cpp
bool operator==(Transaction* t) const override {
    auto * s = dynamic_cast<MoneyTransaction*>(t);
    return amount == s->amount && target == s->target;
}
```
<h4>Serialization methods <a name="sub_section_serialization"></a></h4>
<h5>Constructor</h5>
```cpp
explicit Transaction();
```
For serialization, you need an empty default constructor.
<h5>Transaction::toElement</h5>
```cpp
Element* toElement() const override;
```
This method is used to transform the object into an Element so it can easily be serialized
<h6>Example:</h6>
```cpp
Element* MoneyTransaction::toElement() const {
    ElementObject* e = ElementCreator::object();
    return e->put("type", ElementCreator::create(get_type()))
            ->put("amount", ElementCreator::create(amount))
            ->put("target", ElementCreator::create(target));
}
```
The Element system is the key for serialization. You just have to fill all of the fields and their values. If you are using many differents type of Transactions, you should use a type to help your serializer.

<h5>Transaction::fromElement</h5>
```cpp
void fromElement(ElementObject*, const Serializer*, const char* encoding) override;
```
This method is the opposite than toElement. It is used to build the object with a given Element object.
<h6>Example:</h6>
```cpp
void MoneyTransaction::fromElement(ElementObject* e, const Serializer*, const char*) {
    e->getItem("amount", &amount);
    e->getItem("target", &target);
}
```
### UI methods <a name="sub_section_ui"></a>
<h5>Transaction::description</h5>
```cpp
std::string description() const override;
```
This method is used to show the description of the transaction in the UI for the user to choose.
<h6>Example:</h6>
```cpp
std::string MoneyTransaction::description() const {
    return "give money";
}
```
<h5>Transaction::fill_data</h5>
```cpp
void fill_data() override;
```
This method is used to ask the user to fill the transaction's data
<h6>Example:</h6>
```cpp
void MoneyTransaction::fill_data() {
    do {
        std::cout << "Amount of money: " << std::endl;
        std::cin >> amount;
    }while(amount < 0);
    std::cout << "Target key: " << std::endl;
    std::cin >> target;
    std::cout << "Money transaction created" << std::endl;
}
```
<h5>Transaction::clone</h5>
```cpp
Transaction* clone() override;
```
This method is used to create a new object of the same class.
<h6>Example:</h6>
```cpp
Transaction* MoneyTransaction::clone() {
    return new MoneyTransaction;
}
```
<h4>Database methods <a name="sub_section_database"></a></h4>
<h5>Transaction::apply</h5>
```cpp
std::vector<std::string> apply(Row* row) override;
```
This method is used to apply changes into a database.
It returns a list of users to apply the reverse transaction
<h6>Example:</h6>
```cpp
std::vector<std::string> MoneyTransaction::apply(Row* row){
    auto * cr = dynamic_cast<CustomRow*>(row);
    cr->money -= amount;
    std::vector<std::string> targets;
    targets.push_back(target);
    return  targets;
}
```
<h5>Transaction::apply_reverse</h5>
```cpp
void apply_reverse(Row* row) override;
```
This method is used to apply the reverse transaction changes into a database.
<h6>Example:</h6>
```cpp
void MoneyTransaction::apply_reverse(Row* row){
    auto * cr = dynamic_cast<CustomRow*>(row);
    cr->money += amount;
}
```
<h5>Transaction::createRow</h5>
```cpp
Row* createRow() const override;
```
Creates a row in the database. Since Rows are custom objects from the developer, it cannot be generated by the framework, so the transactions are generating it.
<h6>Example:</h6>
```cpp
Row* MoneyTransaction::createRow() const {
    return new CustomRow();
};
```
<h5>Transaction::validate</h5>
```cpp
bool validate(Row *row) const override;
```
This method is used to check if the transaction is valid and can be add to the block chain
<h5>Example:</h5>
```cpp
bool MoneyTransaction::validate(Row *row) const {
    auto * cr = dynamic_cast<CustomRow*>(row);
    return amount >= cr->money;
}
```
### Reward <a name="section_reward"></a>
The reward is a very particular kind of Transaction.
You only have to override the methods ```Reward::clone``` and ```Reward::createRow```.
### TransactionManager <a name="section_transactionManager"></a>
The transaction manager is a built in class from the framework. You only need to give it a list of transactions, and then to give it to the Node object.
```cpp
TransactionManager manager;
manager.put(new StatusTransaction);
manager.put(new MoneyTransaction);
manager.put(new MessagesTransaction);
node.start(manager);
```
The provided TransactionManager class allows you to easily run every type of transactions without implementing anything. <br />
However, this class is a helper, you can easily manage the transactions creation by yourself without this class. <br />
If you choose this solution, you only have to use the Node::request_transaction method in order to process your transactions.<br />
It can also be replaced by the [Framework helper](#section_framework).
### Serializer <a name="section_serializer"></a>
The serialization class is used to transform Objects into string using Elements and strings into Objects using Elements.
To use this class, you need to register your own transactions with a lambda expression
<h5>Serializer::unserializeTransaction</h5>
```cpp
void add_transaction(int id, std::function<Transaction*()> transaction);
```
<h6>Example:</h6>
```cpp
serial->add_transaction(money->get_type(), []() -> Transaction*{return new MoneyTransaction;});
```
It can also be replaced by the [Framework helper](#section_framework).
### Proof <a name="section_proof"></a>
Proofs are the basis of block chain validation. Some proofs are implemented, but not all of them. Therefore, you can create your own proof and send it to the framework.
<h4>New proof <a name="sub_section_newproof"></a></h4>
A new proof class needs to implements 2 methods
<h5>Proof::run</h5>
```cpp
virtual void run(Block* block, std::string key) = 0;
```
This method will be called to generate the proof, and it will create a new Metadata for the current block.
<h6>Example:</h6>
```cpp
void ProofOfWork::run(Block* block, std::string key){
    Hash tmp((block->parent_fingerprint != nullptr ? block->parent_fingerprint->to_string() : "0") + key);
    for(long long int i = 1; i > 0 ; i++){
        Hash t(&tmp, i);
        for(long long int j = 1; j > 0 ; j++) {
            Hash h(&t, j);
            if(h.to_string().substr(0, 1) == "0"){
                block->data = new ProofOfWorkMetadata(i, j, key);
                return;
            }
        }
    }
}
```
<h5>Proof::accept</h5>
```cpp
virtual bool accept(Block* block, Message*) = 0;
```
This method will be called to check is the metadata generated by the method run by another peer is correct. <br/>
If it is not correct, it means the peer is generating false data, therefore the block must be rejected
<h6>Example:</h6>
```cpp
bool ProofOfWork::accept(Block* block, Message* m){
    auto data = dynamic_cast<ProofOfWorkMetadata*>(block->data);
    Hash tmp((block->parent_fingerprint != nullptr ? block->parent_fingerprint->to_string() : "0") + data->winner);
    Hash t(&tmp, data->first);
    Hash h(&t, data->second);
    return h.to_string().substr(0, 1) == "0";
}
```
<h4>Feed the framework <a name="sub_section_feedframework"></a></h4>
Once your proof is done, you just have to give it to the framework using this method:
```cpp
static void Proof::add_proof(int id, std::function<Proof*()> proof);
```
The id needs to be passed to the Node object. The second parameter is a lambda expression that creates the proof.
<h6>Example:</h6>
```cpp
Proof::add_proof(Proof::WORK, []() -> Proof*{return new ProofOfWork;});
```
<h4>New metadata <a name="sub_section_newmetadata"></a></h4>
If your proof require a new metadata class, you just have to provide this metadata to the serializer using this method.
```cpp
void add_metadata(int id, std::function<Metadata*()> metadata);
```
<h6>Example:</h6>
```cpp
serial->add_metadata(CustomMetadata::TYPE, []() -> Metadata*{return new CustomMetadata;});
```
### Database <a name="section_database"></a>
The database is basically a map of Row. Rows are pure abstract classes that needs to be implemented, because their structure depends of your implementation <br/>
There are 3 methods that must be implemented.
<h5>Row::clone</h5>
```cpp
virtual Row* clone() const = 0;
```
Like Transactions, you need to duplicate the Row in order to accept differents states on differents blocks in the block chain
<h6>Example:</h6>
```cpp
Row* CustomRow::clone() const{
    auto r = new CustomRow;
    r->money = money;
    r->status = status;
    r->messages = messages;
    return r;
}
```
<h5>Row::to_string</h5>
```cpp
virtual std::string to_string() const = 0;
```
Like Transactions, you need a visual representation of the database
<h6>Example:</h6>
```cpp
std::string CustomRow::to_string() const {
    std::string str;
    str += "[" + status + "] (value: " + std::to_string(money) + ")\n";
    for(auto& a : messages)
        str += " - " + a + "\n";
    return str;
}
```
<h5>Row::reward</h5>
```cpp
virtual void reward() = 0;
```
The reward method is called to reward the user who validated the block
<h6>Example:</h6>
```cpp
void CustomRow::reward() {
    money += 1;
}
```
### Framework <a name="section_framework"></a>
In order to make the creation of the different tools easier, the framework provides an important (but not required) helper class, Framework. <br />
This class only needs a list of Transaction as input and generates both TransactionManager and Serializer.
```cpp
void Framework::add_transaction(Transaction* transaction);
```
<h6>Example:</h6>
```cpp
Framework block_chain;
block_chain.add_transaction(new StatusTransaction);
block_chain.add_transaction(new MoneyTransaction);
block_chain.add_transaction(new MessagesTransaction);

//Get the manager
auto manager = block_chain.generate_manager();

//Get the serializer
auto serial = block_chain.generate_serializer();
```
## TODO-List <a name="section_todo"></a>
### Hash <a name="sub_section_hash"></a>
For now, there is only one hash class based on md5. <br/>
It will be changed to make this hash class abstract with the possibility for the user to create his own hash class (And to keep some basic hash functions).

### Cryptography <a name="sub_section_cryptography"></a>
For now, there is only one cryptography class based on RSA. <br/>
It will be changed to make this cryptography class abstract with the possibility for the user to create his own cryptography class (And to keep some basic cryptography functions).

### Proof <a name="sub_section_proof"></a>
For now, there is only one proof: the proof of work. <br/>
The framework will be updated with new proofs

### Header files <a name="sub_section_header"></a>
For now, the installation of the framework is simple by copying files.<br/>
A complete version of the program will run with header files and DLL files.

