//
// Created by default on 3/4/2561.
//

#ifndef BLOCK_CHAIN_CLIENT_H
#define BLOCK_CHAIN_CLIENT_H

#include <algorithm>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/x509.h>
#include <iostream>
#include "chain/NodeState.h"
#include "utils/socket/SocketServer.h"
#include "utils/socket/Peer.h"
#include "algorithm/RSA.h"
#include "kernel/messages/Message.h"
#include "chain/block/proof/Proof.h"
#include "TransactionManager.h"
#include "kernel/parsers/MessageParser.h"
#include "kernel/parsers/BlockAskParser.h"
#include "kernel/parsers/BlockAnswerParser.h"
#include "kernel/parsers/BlockParser.h"
#include "kernel/parsers/SignInParser.h"
#include "kernel/parsers/SignOutParser.h"
#include "kernel/parsers/TransactionParser.h"
#include "kernel/parsers/PeersAnswerParser.h"
#include "kernel/parsers/PeersAskParser.h"
#include "kernel/messages/TransactionMessage.h"
#include "kernel/messages/BlockAskMessage.h"
#include "kernel/messages/SignOutMessage.h"
#include "kernel/messages/AskPeersMessage.h"

class Node{
    friend class Parser;
    friend class PeersAnswerParser;
    friend class PeersAskParser;
    friend class SignInParser;
    friend class SignOutParser;
    friend class TransactionParser;
    friend class BlockParser;
    friend class BlockAskParser;
    friend class BlockAnswerParser;
public:
    Node(Serializer* serializer, int p = 3000, const char* e = "json", int pr = Proof::WORK, bool d = false, Reward* r = nullptr);
    ~Node();
    void close();
    void request_transaction(Transaction* transaction);
    bool static defaultCallback(Socket* socket, int port, Serializer* serializer, Node* node);
    void start(TransactionManager manager);

private:
    void init_parsers();
    void add_parser(MessageParser* p);
    std::map<int, MessageParser*> parsers;
    bool debug;
    std::string encoding;
    Proof* proof;
    void store(std::string ip, int p);
    Serializer* serializer;
    SocketServer server;
    NodeState block_chain;
    Peer self;
    std::vector<Peer> peers;
    std::thread running;
    RSA_Cryptography rsa;
    int queue;
    typedef void(Node::* Message_action)(Message* message);
    void static async(Message* message, Node* node);
    std::vector<Block*> waiting;
    int load(Block *pBlock);
};

#endif //BLOCK_CHAIN_CLIENT_H