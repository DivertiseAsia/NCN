//
// Created by default on 4/4/2561.
//

#ifndef BLOCK_CHAIN_PEER_H
#define BLOCK_CHAIN_PEER_H

#include <string>
#include "Socket.h"
#include "../Serializer.h"
#include "../chain/block/transaction/Transaction.h"

class Peer {
    friend class Node;
public:
    Peer(Serializer* s, std::string str, int c, int t, int b);
    void sign_out(Peer p) const;
    void send(Transaction* transaction);
private:
    Socket* socket;
    Socket* transaction_socket;
    Socket* block_socket;
    Serializer* serializer;
};


#endif //BLOCK_CHAIN_PEER_H
