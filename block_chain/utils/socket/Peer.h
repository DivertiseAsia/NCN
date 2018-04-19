//
// Created by default on 4/4/2561.
//

#ifndef BLOCK_CHAIN_PEER_H
#define BLOCK_CHAIN_PEER_H

#include <string>
#include "Socket.h"
#include "../serialization/Serializer.h"
#include "../../chain/block/transaction/Transaction.h"

class Peer {
    friend class Node;
    friend class PeersAnswerParser;
    friend class SignInParser;
    friend class SignOutParser;
    friend class TransactionParser;
    friend class BlockParser;
    friend class BlockAskParser;
    friend class BlockAnswerParser;
public:
    Peer(Serializer* s, std::string str, int c);
    void close();
    int send(const char* text);
    std::string to_string() const;
    bool operator==(Peer const& p) const{
        return to_string() == p.to_string();
    }
private:
    Serializer* serializer;
    Socket* socket;
    std::string _ip;
    int _port;
};


#endif //BLOCK_CHAIN_PEER_H
