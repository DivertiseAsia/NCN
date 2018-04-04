//
// Created by default on 3/4/2561.
//

#include "Client.h"

Client::Client(int p, int p_t, int p_b): server(p), transactions_listener(this, p_t), blocks_listener(this, p_b) {
    peers.push_back(Peer(p, p_t, p_b));
}

Client::~Client(){
    close();
}
void Client::connect(){
    store();
    load();
    transactions_listener.start(listen<Transaction*>);
    blocks_listener.start(listen<Block>);
}
void Client::load(){
    //TODO
    //Get the file
    block_chain.read_blocks();
}
void Client::store(){
    //TODO
    //Peer peer(p, p_t, p_b)
    //peers.push_back(peer);
    //peer.connect(*peers.begin());
}
void Client::close(){
    for(std::vector<Peer>::const_iterator it = peers.begin(); it != peers.end(); it++)
        it->sign_out(*peers.begin());
}
void Client::request_transaction(){
    auto * transaction = new Transaction();
    //TODO: broadcast to the network
}
bool Client::operator()(Transaction* transaction) {
    bool valid = validator(transaction);
    if(valid) {
        Block *block = block_chain.add(transaction);
        if(block != nullptr){
            //TODO: broadcast to the network
        }
    }
    return valid;
}
bool Client::operator()(Block const& block) {
    bool valid = validator(block);
    if(valid)
        block_chain.add(block);
    return valid;
}