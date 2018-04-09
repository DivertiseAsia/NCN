//
// Created by default on 3/4/2561.
//

#include "Node.h"
void run(SocketServer* server, Serializer* serializer, Node* node) {
    server->run(serializer, node);
}

void listen(bool(* callback)(Socket*, int, Serializer*, Node*), Node* client, int port, Serializer* serializer){
    SocketServer server(port);
    server.run(callback, serializer, client);
}

Node::Node(Validator* v, Serializer* s, int p, int p_t, int p_b): serializer(s), validator(v), server(p), transactions_listener(this, p_t, s), blocks_listener(this, p_b, s), running(run, &server, s, this) {

    OpenSSL_add_all_algorithms();
    ERR_load_BIO_strings();
    ERR_load_crypto_strings();
    if(!rsa.backup())
        rsa.generate();
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
    transactions_listener.start(Node::transactionsCallback, listen);
    blocks_listener.start(Node::blocksCallback, listen);
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
    Message message(serializer->serialize(transaction, "json"), rsa.encrypt(serializer->serialize(transaction, "json")), rsa.getPublicKey());
    for(std::vector<Peer>::iterator it = peers.begin(); it != peers.end(); it++)
        it->send(serializer->serialize(&message, "json"));
}

bool Node::operator()(Transaction* transaction) {
    bool valid = (*validator)(transaction);
    if(valid) {
        Block *block = block_chain.add(transaction);
        if(block != nullptr){
            Message message(serializer->serialize(block, "json"), rsa.encrypt(serializer->serialize(block, "json")), rsa.getPublicKey());
            for(std::vector<Peer>::iterator it = peers.begin(); it != peers.end(); it++)
                it->send(serializer->serialize(&message, "json"));
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

bool Node::operator()(Message* message) {
    bool valid = true;
    std::cout << "Decrypted: ";
    std::cout << " test"<< std::endl;
    return valid;
}


bool Node::transactionsCallback(Socket* socket, int port, Serializer* serializer, Node* node) {
    std::string buffer;
    socket->read(buffer);
    if(buffer.length()){
        auto start = std::chrono::high_resolution_clock::now();
        std::cout << "Request received on port " << port  <<std::endl;
        Message* message = serializer->unserializeMessage(buffer, "json");
        RSA_Cryptography crypto(message->public_key);
        Transaction* deciphered(serializer->unserializeTransaction(crypto.decrypt(message->getCipher(), message->size), "json"));
        Transaction* plain_text(serializer->unserializeTransaction(message->plain_text, "json"));
        if(*deciphered == plain_text)
            (*node)(plain_text);

        delete deciphered;
        delete socket;
        auto end = std::chrono::high_resolution_clock::now();
        long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        std::cout << "Request performed in "<< (microseconds/1000.0) << " milliseconds" <<std::endl;
    }
    return true;
}

bool Node::blocksCallback(Socket* socket, int port, Serializer* serializer, Node* node) {
    std::string buffer;
    socket->read(buffer);
    if(buffer.length()){
        auto start = std::chrono::high_resolution_clock::now();
        std::cout << "Request received on port " << port << std::endl;
        Message* message = serializer->unserializeMessage(buffer, "json");
        RSA_Cryptography crypto(message->public_key);
        Block* deciphered(serializer->unserializeBlock(crypto.decrypt(message->getCipher(), message->size), "json"));
        Block* plain_text(serializer->unserializeBlock(message->plain_text, "json"));
        if(*deciphered == plain_text)
            (*node)(plain_text);

        delete deciphered;
        delete socket;
        delete socket;
        auto end = std::chrono::high_resolution_clock::now();
        long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        std::cout << "Request performed in "<< (microseconds/1000.0) << " milliseconds" <<std::endl;
    }
    return true;
}
