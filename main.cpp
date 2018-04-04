#include <iostream>

#include "block_chain/Client.h"
int main() {
    Client client;
    client.connect();
    std::cout << "Hello, World!" << std::endl;
    return 0;
}