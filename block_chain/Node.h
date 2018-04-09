//
// Created by default on 3/4/2561.
//

#ifndef BLOCK_CHAIN_CLIENT_H
#define BLOCK_CHAIN_CLIENT_H

#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <iostream>
#include "chain/NodeState.h"
#include "Validator.h"
#include "Listener.h"
#include "socket/SocketServer.h"
#include "socket/Peer.h"
#include "../include/RSA.h"
#include "../include/Message.h"
#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/x509.h>

class Node{
public:
    Node(Validator* v, Serializer* serializer, int p = 3000, int p_t = 3001, int p_b = 3002);
    ~Node();
    void close();
    void request_transaction(Transaction* transaction);
    bool operator()(Transaction* transaction);
    bool operator()(Block* block);
    bool operator()(Message* message);
private:
    void connect();
    void load();
    void store();
    Serializer* serializer;
    //Server to send data
    Validator* validator;
    SocketServer server;
    NodeState block_chain;
    Listener transactions_listener;
    Listener blocks_listener;
    std::vector<Peer> peers;
    std::thread running;
    RSA_Cryptography rsa;
    bool static transactionsCallback(Socket* socket, int port, Serializer* serializer, Node* node);
    bool static blocksCallback(Socket* socket, int port, Serializer* serializer, Node* node);
};

#endif //BLOCK_CHAIN_CLIENT_H

/*
Passing on valid blocks
Passing on valid transactions
‘Mining’ the blocks
 */
