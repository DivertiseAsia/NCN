#include <iostream>

#include "block_chain/Node.h"
#include "transactions/StatusTransaction.h"
#include "validator/CustomSerializer.h"
#include "block_chain/utils/serialization/json/JsonCreator.hpp"
#include "block_chain/utils/serialization/json/JsonParser.hpp"
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
    Serializer* serial = new CustomSerializer();
    serial->set_serializer("json", new JsonCreator());
    serial->set_unserializer("json", new JsonParser());
    Node client(new Validator(), serial, 3001);
    Transaction* t = new StatusTransaction("The Game");
    client.request_transaction(t);
    usleep(1000000);
    //usleep(3000000);
    //while(1);//{std::cout<<"t";client.request_transaction(t);std::cout<<"t"<<std::endl;}
    return 0;
}
