//
// Created by default on 3/4/2561.
//

#include "Node.h"
void run(SocketServer* server) {
    server->run();
}
Node::Node(Validator* v, Serializer* serializer, int p, int p_t, int p_b): validator(v), server(p), transactions_listener(this, p_t, serializer), blocks_listener(this, p_b, serializer), running(run, &server) {
    connect();
    peers.push_back(Peer(serializer, std::string("127.0.0.1"), p, p_t, p_b));
}

Node::~Node(){
    close();
    delete validator;
    std::terminate();
}
void Node::connect(){
    store();
    load();
    transactions_listener.start(Node::transactionsCallback, listen<Transaction*>);
    blocks_listener.start(Node::blocksCallback, listen<Block*>);
}
void Node::load(){
    //TODO
    //Get the file
    block_chain.read_blocks();
}
void Node::store(){
    //TODO
    //Peer peer(p, p_t, p_b)
    //peers.push_back(peer);
    //peer.connect(*peers.begin());
}
void Node::close(){
    for(std::vector<Peer>::iterator it = peers.begin(); it != peers.end(); it++)
        it->sign_out(*peers.begin());
}
void Node::request_transaction(Transaction* transaction){
    for(std::vector<Peer>::iterator it = peers.begin(); it != peers.end(); it++)
        it->send(transaction);
    //TODO: broadcast to the network
}
bool Node::operator()(Transaction* transaction) {
    bool valid = (*validator)(transaction);
    if(valid) {
        Block *block = block_chain.add(transaction);
        if(block != nullptr){
            //TODO: broadcast to the network
        }
    }
    return valid;
}
bool Node::operator()(Block* block) {
    bool valid = (*validator)(block);
    if(valid)
        block_chain.add(block);
    return valid;
}


bool Node::transactionsCallback(Socket* socket, int port, Serializer* serializer) {
    std::string buffer;
    socket->read(buffer);
    if(buffer.length()){
        auto start = std::chrono::high_resolution_clock::now();
        std::cout << "Request received on port " << port << " : " << buffer <<std::endl;
        //TODO: unserialize buffer.c_str() into transaction

        delete socket;
        auto end = std::chrono::high_resolution_clock::now();
        long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        std::cout << "Request performed in "<< (microseconds/1000.0) << " milliseconds" <<std::endl;
    }

    return true;
}

bool Node::blocksCallback(Socket* socket, int port, Serializer* serializer) {
    std::string buffer;
    socket->read(buffer);
    if(buffer.length()){
        auto start = std::chrono::high_resolution_clock::now();
        std::cout << "Request received on port " << port << " : " << buffer <<std::endl;
        //TODO: unserialize buffer.c_str() into block
        delete socket;
        auto end = std::chrono::high_resolution_clock::now();
        long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        std::cout << "Request performed in "<< (microseconds/1000.0) << " milliseconds" <<std::endl;
    }

    return true;
}