//
// Created by default on 3/4/2561.
//

#ifndef BLOCK_CHAIN_LISTENER_H
#define BLOCK_CHAIN_LISTENER_H

#include <thread>
#include "socket/SocketServer.h"

class Client;
class Listener {
public:
    Listener(Client* client, int p);
    ~Listener();
    void start(void (*func)(Client*, int p));
private:
    Client* client;
    std::thread* thread;
    int port;
};


#endif //BLOCK_CHAIN_LISTENER_H
