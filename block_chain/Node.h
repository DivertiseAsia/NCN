//
// Created by default on 3/4/2561.
//

#ifndef BLOCK_CHAIN_CLIENT_H
#define BLOCK_CHAIN_CLIENT_H

#include <iostream>
#include "chain/NodeState.h"
#include "Validator.h"
#include "Listener.h"
#include "socket/SocketServer.h"
#include "socket/Peer.h"

class Node{
public:
    Node(Validator* v, Serializer* serializer, int p = 3000, int p_t = 3001, int p_b = 3002);
    ~Node();
    void close();
    void request_transaction(Transaction* transaction);
    bool operator()(Transaction* transaction);
    bool operator()(Block* block);
private:
    void connect();
    void load();
    void store();
    //Server to send data
    SocketServer server;
    NodeState block_chain;
    Validator* validator;
    Listener transactions_listener;
    Listener blocks_listener;
    std::vector<Peer> peers;
    std::thread running;

    bool static transactionsCallback(Socket* socket, int port);
    bool static blocksCallback(Socket* socket, int port);
};


template <typename T> void listen(bool(* callback)(Socket*, int), Node* client, int port){
    SocketServer server(port);
    server.run(callback);
    T object;
    (*client)(object);
}
#endif //BLOCK_CHAIN_CLIENT_H

/*
Passing on valid blocks
Passing on valid transactions
‘Mining’ the blocks
 */