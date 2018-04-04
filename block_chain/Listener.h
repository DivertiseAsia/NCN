//
// Created by default on 3/4/2561.
//

#ifndef BLOCK_CHAIN_LISTENER_H
#define BLOCK_CHAIN_LISTENER_H

#include <thread>
#include "socket/SocketServer.h"

class Node;
class Listener {
public:
    Listener(Node* client, int p);
    ~Listener();
    void start(bool(* callback)(Socket*, int), void (*func)(bool(* callback)(Socket*, int), Node*, int p));
private:
    Node* client;
    std::thread* thread;
    int port;
};


#endif //BLOCK_CHAIN_LISTENER_H
