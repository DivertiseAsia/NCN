#include <iostream>

#include "block_chain/Node.h"
#include "transactions/StatusTransaction.h"
#include "validator/CustomValidator.h"
#include "validator/CustomSerializer.h"
#include "block_chain/utils/serialization/json/JsonCreator.hpp"
#include "block_chain/utils/serialization/json/JsonParser.hpp"
#include <cstdio>
#include <cstring>
/*
 * ls -R ./block_chain | awk '
/:$/&&f{s=$0;f=0}
/:$/&&!f{sub(/:$/,"");s=$0;f=1;next}
NF&&f{ print s"/"$0 }'| sed ':a;N;$!ba;s/\n/ /g'
 */

#include "iostream"
#include "block_chain/utils/RSA.h"
int main() {
    Serializer* serial = new CustomSerializer();
    serial->set_serializer("json", new JsonCreator());
    serial->set_unserializer("json", new JsonParser());
    Node client(new CustomValidator(), serial, 7080, 7081, 7082);
    Transaction* t = new StatusTransaction("The Game");
    client.request_transaction(t);
    while(1);
    return 0;
}
