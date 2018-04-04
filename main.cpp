#include <iostream>

#include "block_chain/Client.h"
#include "transactions/StatusTransaction.h"

int main() {
    Client client;
    client.connect();
    Transaction* t = new StatusTransaction("Test");
    std::cout << "Hello, World!" << std::endl;
    return 0;
}