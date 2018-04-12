#include <iostream>

#include "block_chain/Node.h"
#include "transactions/StatusTransaction.h"
#include "transactions/MessagesTransaction.h"
#include "transactions/MoneyTransaction.h"
#include "validator/CustomSerializer.h"
#include "block_chain/utils/serialization/json/JsonCreator.hpp"
#include "block_chain/utils/serialization/json/JsonParser.hpp"
#include "block_chain/TransactionManager.h"
#include "block_chain/proof/Proof.h"
#include <cstdio>
#include <cstring>
#include <unistd.h>
/*
 * ls -R ./block_chain | awk '
/:$/&&f{s=$0;f=0}
/:$/&&!f{sub(/:$/,"");s=$0;f=1;next}
NF&&f{ print s"/"$0 }'| sed ':a;N;$!ba;s/\n/ /g'
 */

int main() {

    TransactionManager manager;
    manager.put(new StatusTransaction);
    manager.put(new MoneyTransaction);
    manager.put(new MessagesTransaction);
    Serializer* serial = new CustomSerializer();
    serial->set_serializer("json", new JsonCreator());
    serial->set_unserializer("json", new JsonParser());
    Node client(serial, 3007, "json", Proof::WORK);
    //Transaction* t = new StatusTransaction("I lost");
    Transaction* t = nullptr;
    //usleep(1000000);
    /*
    do{
        t = manager.run();
        if(t)
            client.request_transaction(t);
    }while(t != nullptr);*/
    return 0;
}