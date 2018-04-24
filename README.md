# Block-chain Framework
## Overview
This project is a C++ Framework built to allow easy and fast development of any kind of block-chain. \
The idea is to limit the development to transactions and data representation only. No need to implement anything else. \
Of course, as a framework, it needs a big flexibility, therefore, it is possible to write much more advanced block-chain by configuring as many things as you want. \
> Note that everything can change to allow more flexibility.
## Node
The node is the peer itself. You only have to create it and it will run.
```cpp
Node node(config);
```
## Config
The node is the peer itself. You only have to create it and it will run.
```cpp
Config config("configuration file path", serializer, Proof::WORK, reward);
```
The file itself is a json file.
##### Example:
```json
{
  "port": 3423,
  "encoding": "json",
  "debug": true
}
```
the parameters serializer, proof and reward are explained later.
## Transaction
Transactions are the most important thing to implement. \
```cpp
#include "./block_chain/chain/block/transaction/Transaction.h"
```
There is already a pure abstract class to implement, so you basicaly just have to fill the methods for your own Transaction class.
### Useful methods
#### get_type
```cpp
int get_type() const override;
```
This method is used to give a type to a transaction. Each transaction type must have a different type. It is used as an ID.
##### Example:
```cpp
int MoneyTransaction::get_type() const {
    return 2;
}
```
#### ==
```cpp
bool operator==(Transaction* t) const override
```
This method is used to check if two transactions are the same
##### Example:
```cpp
bool operator==(Transaction* t) const override {
    auto * s = dynamic_cast<MoneyTransaction*>(t);
    return amount == s->amount && target == s->target;
}
```
### Serialization methods
#### Constructor
```cpp
explicit Transaction();
```
For serialization, you need an empty default constructor.
#### toElement
```cpp
Element* toElement() const override;
```
This method is used to transform the object into an Element so it can easily be serialized
##### Example:
```cpp
Element* MoneyTransaction::toElement() const {
    ElementObject* e = ElementCreator::object();
    return e->put("type", ElementCreator::create(get_type()))
            ->put("amount", ElementCreator::create(amount))
            ->put("target", ElementCreator::create(target));
}
```
The Element system is the key for serialization. You just have to fill all of the fields and their values. If you are using many differents type of Transactions, you should use a type to help your serializer.

#### fromElement (protected)
```cpp
void fromElement(ElementObject*, const Serializer*, const char* encoding) override;
```
This method is the opposite than toElement. It is used to build the object with a given Element object.
##### Example:
```cpp
void MoneyTransaction::fromElement(ElementObject* e, const Serializer*, const char*) {
    e->getItem("amount", &amount);
    e->getItem("target", &target);
}
```
### UI methods
#### description
```cpp
std::string description() const override;
```
This method is used to show the description of the transaction in the UI for the user to choose.
##### Example:
```cpp
std::string MoneyTransaction::description() const {
    return "give money";
}
```
#### fill_data
```cpp
void fill_data() override;
```
This method is used to ask the user to fill the transaction's data
##### Example:
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
#### clone
```cpp
Transaction* clone() override;
```
This method is used to create a new object of the same class.
##### Example:
```cpp
Transaction* MoneyTransaction::clone() {
    return new MoneyTransaction;
}
```
### Database methods
#### apply
```cpp
std::vector<std::string> apply(Row* row) override;
```
This method is used to apply changes into a database.
It returns a list of users to apply the reverse transaction
##### Example:
```cpp
std::vector<std::string> MoneyTransaction::apply(Row* row){
    auto * cr = dynamic_cast<CustomRow*>(row);
    cr->money -= amount;
    std::vector<std::string> targets;
    targets.push_back(target);
    return  targets;
}
```
#### apply_reverse
```cpp
void apply_reverse(Row* row) override;
```
This method is used to apply the reverse transaction changes into a database.
##### Example:
```cpp
void MoneyTransaction::apply_reverse(Row* row){
    auto * cr = dynamic_cast<CustomRow*>(row);
    cr->money += amount;
}
```
#### createRow
```cpp
Row* createRow() const override;
```
Creates a row in the database. Since Rows are custom objects from the developper, it cannot be generated by the framework, so the transactions are generating it.
##### Example:
```cpp
Row* MoneyTransaction::createRow() const {
    return new CustomRow();
};
```
#### validate
```cpp
bool validate(Row *row) const override;
```
This method is used to check if the transaction is valid and can be add to the block chain
##### Example:
```cpp
bool MoneyTransaction::validate(Row *row) const {
    auto * cr = dynamic_cast<CustomRow*>(row);
    return amount >= cr->money;
}
```
## Reward
The reward is a very particular kind of Transaction.
You only have to override the methods ```clone``` and ```createRow```.
## TransactionManager
The transaction manager is a built in class from the framework. You only need to give it a list of transactions, and then to give it to the Node object.
```cpp
TransactionManager manager;
manager.put(new StatusTransaction);
manager.put(new MoneyTransaction);
manager.put(new MessagesTransaction);
node.start(manager);
```
## Serializer
The serialization class is used to transfrom Objects into string using Elements and strings into Objects using Elements.
One method from this class needs to be overridden:
```cpp
virtual Transaction* unserializeTransaction(std::string transaction, const char* encoding) const;
```
It need to be overridden because the framework doesn't know about your transactions, therefore, you have to implement this method using the Serializer methods
##### Example:
```cpp
Transaction* CustomSerializer::unserializeTransaction(std::string transaction, const char* key) const {
    ElementObject* e = getElement(transaction, key);
    int type;
    e->getItem("type", &type);
    Transaction* t;
    if(!type)
        t = new StatusTransaction();
    else
        t = new MessagesTransaction();
    t->__init__(e, this, key);
    return t;
}
```
## Proof
Proofs are ## run
the basis of block chain validation. Some proofs are implemented, but not all of them. Therefore, you can create your own proof and send it to the framework.
### New proof
A new proof class needs to implements 2 methods
#### run
```cpp
virtual void run(Block* block, std::string key) = 0;
```
This method will be called to generate the proof, and it will create a new Metadata for the current block.
##### Example:
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
#### accept
```cpp
virtual bool accept(Block* block, Message*) = 0;
```
This method will be called to check is the metadata generated by the method run by another peer is correct. \
If it is not correct, it means the peer is generating false data, therefore the block must be rejected
##### Example:
```cpp
bool ProofOfWork::accept(Block* block, Message* m){
    auto data = dynamic_cast<ProofOfWorkMetadata*>(block->data);
    Hash tmp((block->parent_fingerprint != nullptr ? block->parent_fingerprint->to_string() : "0") + data->winner);
    Hash t(&tmp, data->first);
    Hash h(&t, data->second);
    return h.to_string().substr(0, 1) == "0";
}
```
### Give the proof to the framework
One your proof is done, you just have to give it to the framework using this method:
```cpp
static void Proof::add_proof(int id, std::function<Proof*()> proof);
```
The id needs to be passed to the Node object. The second parameter is a lambda that creates the proof.
##### Example:
```cpp
Proof::add_proof(Proof::WORK, []() -> Proof*{return new ProofOfWork;});
```
## Database
The database is basically a map of Row. Rows are pure abstract classes that needs to be implemented, because their structure depends of your implementation \
There are 3 methods that must be implemented.
#### clone
```cpp
virtual Row* clone() const = 0;
```
Like Transactions, you need to duplicate the Row in order to accept differents states on differents blocks in the block chain
##### Example:
```cpp
Row* CustomRow::clone() const{
    auto r = new CustomRow;
    r->money = money;
    r->status = status;
    r->messages = messages;
    return r;
}
```
#### to_string
```cpp
virtual std::string to_string() const = 0;
```
Like Transactions, you need a visual representation of the database
##### Example:
```cpp
std::string CustomRow::to_string() const {
    std::string str;
    str += "[" + status + "] (value: " + std::to_string(money) + ")\n";
    for(auto& a : messages)
        str += " - " + a + "\n";
    return str;
}
```
#### reward
```cpp
virtual void reward() = 0;
```
The reward method is called to reward the user who validated the block
##### Example:
```cpp
void CustomRow::reward() {
    money += 1;
}
```
## TODO-List
### Hash
For now, there is only one hash class based on md5. \
It will be changed to make this hash class abstract with the possibility for the user to create his own hash class (And to keep some basic hash functions).

### Cryptography
For now, there is only one cryptography class based on RSA. \
It will be changed to make this cryptography class abstract with the possibility for the user to create his own cryptography class (And to keep some basic cryptography functions).

### Proofs
For now, there is only one proof: the proof of work. \
The framework will be updated with new proofs
