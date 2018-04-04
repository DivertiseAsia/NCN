#include <iostream>

#include "block_chain/Node.h"
#include "transactions/StatusTransaction.h"
#include "validator/CustomValidator.h"

int main() {
    Node client(new CustomValidator(), new Serializer(), 7050, 7051, 7052);
    Transaction* t = new StatusTransaction("The Game");
    client.request_transaction(t);
    while(1);
    return 0;
}