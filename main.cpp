#include <iostream>

#include "block_chain/Node.h"
#include "transactions/StatusTransaction.h"
#include "validator/CustomValidator.h"
#include "include/CustomSerializer.h"
#include "block_chain/utils/serialization/json/JsonCreator.hpp"
#include "block_chain/utils/serialization/json/JsonParser.hpp"

int main() {
    Serializer* serial = new CustomSerializer();
    serial->set_serializer("json", new JsonCreator());
    serial->set_unserializer("json", new JsonParser());
    Node client(new CustomValidator(), serial, 7050, 7051, 7052);
    Transaction* t = new StatusTransaction("The Game");
    client.request_transaction(t);
    while(1);
    return 0;
}
