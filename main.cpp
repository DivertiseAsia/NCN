#include <iostream>

#include "block_chain/Node.h"
#include "transactions/StatusTransaction.h"
#include "validator/CustomValidator.h"

int main() {
    Node client(new CustomValidator(), new Serializer(), 7047, 7048, 7049);
    Transaction* t = new StatusTransaction("The Game");
    client.request_transaction(t);
    std::cout << "Hello, World!" << std::endl;
    while(1);
    return 0;
}