#include <iostream>

#include "serializer/CustomSerializer.h"
#include "block_chain/Node.h"
#include "block_chain/TransactionManager.h"
#include "block_chain/proof/Proof.h"
#include "transactions/StatusTransaction.h"
#include "transactions/MessagesTransaction.h"
#include "transactions/MoneyTransaction.h"
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
//TODO: looks like the database is not duplicated -> multiples and same values, need to inspect that
int main() {
    //Custom block chain
    std::string encoding("json");
    Serializer* serial = new CustomSerializer();
    TransactionManager manager;
    manager.put(new StatusTransaction);
    manager.put(new MoneyTransaction);
    manager.put(new MessagesTransaction);

    //initialization of the block chain
    ElementObject* o = read_config("./config.json", serial, encoding.c_str());
    int port;
    o->getItem("port", &port);
    Node client(serial, port, encoding.c_str(), Proof::WORK, true);
    //launching the software
    client.start(manager);
    delete o;
    return 0;
}
