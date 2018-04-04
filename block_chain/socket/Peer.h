//
// Created by default on 4/4/2561.
//

#ifndef BLOCK_CHAIN_PEER_H
#define BLOCK_CHAIN_PEER_H


class Peer {
public:
    Peer(int c, int t, int b);
    void sign_out(Peer p) const;
    void connect() const;
private:
    int connect_port;
    int transaction_port;
    int block_port;
};


#endif //BLOCK_CHAIN_PEER_H
