//
// Created by default on 3/4/2561.
//

#ifndef BLOCK_CHAIN_CLIENT_H
#define BLOCK_CHAIN_CLIENT_H

#include <algorithm>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <iostream>
#include "chain/NodeState.h"
#include "Validator.h"
#include "socket/SocketServer.h"
#include "socket/Peer.h"
#include "utils/RSA.h"
#include "Message.h"
#include "proof/Proof.h"
#include "TransactionManager.h"
#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/x509.h>


class Node{
public:
    explicit Node(Serializer* serializer, int p = 3000, const char* e = "json", int pr = Proof::WORK, bool d = false);
    ~Node();
    void close();
    void request_transaction(Transaction* transaction);
    bool operator()(Transaction* transaction, Message* message);
    bool operator()(Block* block, Message* message);
    bool operator()(Message* message);
    bool static defaultCallback(Socket* socket, int port, Serializer* serializer, Node* node);
    void start(TransactionManager manager);

private:
    bool debug;
    std::string encoding;
    Proof* proof;
    void load(std::string list);
    void store(std::string ip, int p);
    Serializer* serializer;
    Validator validator;
    SocketServer server;
    NodeState block_chain;
    Peer self;
    std::vector<Peer> peers;
    std::thread running;
    RSA_Cryptography rsa;
    int queue;
    void parseAskPeers(Message* message);
    void parseTransaction(Message* message);
    void parseBlock(Message* message);
    void parseAnswerPeers(Message* message);
    void parseSignIn(Message* message);
    void parseSignOut(Message* message);
    typedef void(Node::* Message_action)(Message* message);
    void static async(Message* message, Node* node);
    std::vector<Block*> waiting;

    int load(Block *pBlock);

    void parseAskBlock(Message *message);

    void parseAnswerBlock(Message *message);
};

#endif //BLOCK_CHAIN_CLIENT_H