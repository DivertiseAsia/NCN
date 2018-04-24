//
// Created by default on 4/4/2561.
//

#ifndef BLOCK_CHAIN_PEER_H
#define BLOCK_CHAIN_PEER_H

#include <string>
#include "Socket.h"
#include "../serialization/Serializer.h"
#include "../../chain/block/transaction/Transaction.h"


/**
 *  @class Peer "block_chain/utils/socket/Peer.h"
 *  A peer is a member of a network.
 *
 *  @author Mathieu Lochet
 *  @version 1
 */
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

    /**
     *  Initialize the peer by creating a socket.
     *
     *  @param str the peer's IP address
     *  @param c the peers's port
     */
    Peer(std::string str, int c);

    /**
     *  Close the peer's socket
     */
    void close();

    /**
     *  Send a request to the peer
     *
     *  @param text the text to be sent
     *  @return 1 if success, 0 if failure
     */
    int send(const char* text);

    /**
     *  visual representation of the peer
     *
     *  @return the string representation of the peer
     */
    std::string to_string() const;

    /**
     *  Check if two peers have the save IP and port
     *
     *  @param p a peer to see if they are the same
     *  @return 1 is they are the same, 0 otherwise
     */
    bool operator==(Peer const& p) const{
        return to_string() == p.to_string();
    }
private:

    /**
     *  The peer's socket
     */
    Socket* socket;

    /**
     *  The peer's IP
     */
    std::string _ip;

    /**
     *  The peer's port
     */
    int _port;
};


#endif //BLOCK_CHAIN_PEER_H
