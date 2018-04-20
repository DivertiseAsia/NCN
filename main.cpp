#include <iostream>

#include "serializer/CustomSerializer.h"
#include "block_chain/Node.h"
#include "block_chain/TransactionManager.h"
#include "block_chain/chain/block/proof/Proof.h"
#include "transactions/StatusTransaction.h"
#include "transactions/MessagesTransaction.h"
#include "transactions/MoneyTransaction.h"
#include "reward/RewardTransaction.h"
/*
 * ls -R ./block_chain | awk '
/:$/&&f{s=$0;f=0}
/:$/&&!f{sub(/:$/,"");s=$0;f=1;next}
NF&&f{ print s"/"$0 }'| sed ':a;N;$!ba;s/\n/ /g'
 */
/*rand() % 1000+3000*/

ElementObject* read_config(const char* filename, Serializer* serial, const char* encoding){
    std::ifstream block_file(filename);
    std::string line;
    std::string serialized;
    if(block_file.is_open()){
        while (std::getline (block_file, line))
            serialized += line;
    }
    return serial->getElement(serialized, encoding);
}

//TODO: a new peers asking for blocks may not be updated by the reward transaction
int main() {
    //Custom block chain
    std::string encoding("json");

    Serializer* serial = new CustomSerializer();
    TransactionManager manager;
    manager.put(new StatusTransaction);
    manager.put(new MoneyTransaction);
    manager.put(new MessagesTransaction);
    Reward* r = new RewardTransaction();

    //initialization of the block chain
    ElementObject* o = read_config("./config.json", serial, encoding.c_str());
    int port;
    o->getItem("port", &port);
    Node client(serial, port, encoding.c_str(), Proof::WORK, true, r);
    //launching the software
    client.start(manager);
    delete o;
    return 0;
}
