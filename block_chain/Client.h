//
// Created by default on 3/4/2561.
//

#ifndef BLOCK_CHAIN_CLIENT_H
#define BLOCK_CHAIN_CLIENT_H

#include <iostream>
#include "chain/Chain.h"
#include "Validator.h"
#include "Listener.h"
#include "socket/SocketServer.h"
#include "socket/Peer.h"

class Client{
public:
    Client(int p = 3000, int p_t = 3001, int p_b = 3002);
    ~Client();
    void connect();
    void load();
    void store();
    void close();
    void request_transaction();
    bool operator()(Transaction* transaction);
    bool operator()(Block const& block);
private:
    //Server to send data
    SocketServer server;
    Chain block_chain;
    Validator validator;
    Listener transactions_listener;
    Listener blocks_listener;
    std::vector<Peer> peers;
};

template <typename T> void listen(Client* client, int port){
    SocketServer server(port);
    server.run();
    T object;
    (*client)(object);
}
#endif //BLOCK_CHAIN_CLIENT_H

/*
Passing on valid blocks
Passing on valid transactions
‘Mining’ the blocks
 */