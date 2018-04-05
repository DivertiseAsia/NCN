//
// Created by default on 3/4/2561.
//

#ifndef BLOCK_CHAIN_LISTENER_H
#define BLOCK_CHAIN_LISTENER_H

#include <thread>
#include "socket/SocketServer.h"
#include "Serializer.h"

class Node;
class Listener {
public:
    Listener(Node* client, int p, Serializer* serializer);
    ~Listener();
    void start(bool(* callback)(Socket*, int, Serializer* serializer), void (*func)(bool(* callback)(Socket*, int, Serializer* serializer), Node*, int p));
private:
    Node* client;
    std::thread* thread;
    int port;
    Serializer* serializer;
};


#endif //BLOCK_CHAIN_LISTENER_H
