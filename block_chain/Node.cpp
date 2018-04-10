//
// Created by default on 3/4/2561.
//

#include "Node.h"
void run(SocketServer* server, Serializer* serializer, Node* node) {
    server->run(Node::defaultCallback, serializer, node);
}

Node::Node(Validator* v, Serializer* s, int p): block_chain(1), serializer(s), validator(v), server(p), running(run, &server, s, this) {
    OpenSSL_add_all_algorithms();
    ERR_load_BIO_strings();
    ERR_load_crypto_strings();
    if(!rsa.backup("/home/default/CLionProjects/block_chain/network/private.pem", "/home/default/CLionProjects/block_chain/network/public.pem"))
        rsa.generate("/home/default/CLionProjects/block_chain/network/private.pem", "/home/default/CLionProjects/block_chain/network/public.pem");
    std::string ip = "127.0.0.1";
    peers.emplace_back(Peer(serializer, ip, p));
    store(ip, p);
    //running.detach();
}

Node::~Node(){
    server.close();
    running.detach();
    close();
    delete validator;
    delete serializer;
}

void Node::load(std::string l){
    Message message(peers.begin()->to_string(), "", "", Message::SIGN_IN);
    char* m = serializer->serialize(&message, "json");
    std::istringstream list(l);
    std::string line;
    while (std::getline (list, line)) {
        unsigned long index = line.find(':');
        std::string ip = line.substr(0, index);
        int port = atoi(line.substr(index+1).c_str());
        std::cout << ip << " --- " << port << std::endl;
        Peer peer(serializer, ip, port);
        peers.emplace_back(peer);
        peer.send(m);
    }
    free(m);
}

void Node::store(std::string _ip, int _p){
    std::ifstream peers_file;
    peers_file.open("/home/default/CLionProjects/block_chain/network/network.nfo", std::ifstream::in);
    if(peers_file.is_open()){
        std::string line;
        Message message(peers.begin()->to_string(), "", "", Message::ASK_PEERS);
        char* m = serializer->serialize(&message, "json");
        while (std::getline (peers_file, line)) {
            unsigned long index = line.find(':');
            std::string ip = line.substr(0, index);
            int port = atoi(line.substr(index+1).c_str());
            Peer peer(serializer, ip, port);
            if(peer.send(m))
                break;
        }
        peers_file.close();
        free(m);
    }
    /*
    */
}
void Node::close(){
    Message message(peers.begin()->to_string(), "", "", Message::SIGN_OUT);
    char* m = serializer->serialize(&message, "json");
    for (auto &peer : peers)
        peer.send(m);
    free(m);
}

void Node::request_transaction(Transaction* transaction){
    transaction->__hash__(serializer, "json");
    Message message(serializer->serialize(transaction, "json"), rsa.encrypt(serializer->serialize(transaction, "json")), rsa.getPublicKey(), Message::TRANSACTION);
    char* m = serializer->serialize(&message, "json");
    for (auto &peer : peers)
        peer.send(m);
    free(m);
}

bool Node::operator()(Transaction* transaction) {
    bool valid = (*validator)(transaction);
    if(valid) {
        Block *block = block_chain.add(transaction);
        //TODO: generate proof of something
        if(block != nullptr){
            std::string serialized_block(serializer->serialize(block, "json"));
            Message message(serialized_block, rsa.encrypt(serialized_block), rsa.getPublicKey(), Message::BLOCK);
            char* m = serializer->serialize(&message, "json");
            for (auto &peer : peers)
                peer.send(m);
            free(m);
        }
    }
    return valid;
}
bool Node::operator()(Block* block) {
    bool valid = (*validator)(block);
    return valid;
}

bool Node::operator()(Message* message) {
    bool valid = true;
    return valid;
}


void Node::parseAnswerPeers(Message* message) {
    load(message->plain_text);
    block_chain.read_blocks();
}

void Node::parseAskPeers(Message* message) {
    unsigned long index = message->plain_text.find(':');
    std::string ip = message->plain_text.substr(0, index);
    int port = atoi(message->plain_text.substr(index+1).c_str());
    Peer peer(serializer, ip, port);
    std::string peers_to_send;
    for (auto &peer : peers)
        peers_to_send += peer.to_string() + std::string("\n");
    message->plain_text = peers_to_send;
    message->type = Message::ANSWER_PEERS;
    char* m = serializer->serialize(message, "json");
    peer.send(m);
    free(m);
}

void Node::parseTransaction(Message* message){
    RSA_Cryptography crypto(message->public_key);
    std::string str(message->getCipher());
    Transaction* deciphered(serializer->unserializeTransaction(crypto.decrypt(str, str.size()), "json"));
    Transaction* plain_text(serializer->unserializeTransaction(message->plain_text, "json"));
    if(*deciphered == plain_text)
        (*this)(plain_text);
    delete deciphered;
    delete plain_text;
}

void Node::parseBlock(Message* message) {
    RSA_Cryptography crypto(message->public_key);
    std::string str(message->getCipher());
    Block* deciphered(serializer->unserializeBlock(crypto.decrypt(str, str.size()), "json"));
    Block* plain_text(serializer->unserializeBlock(message->plain_text, "json"));
    if(*deciphered == plain_text)
        (*this)(plain_text);
    delete deciphered;
    delete plain_text;
}

void Node::parseSignIn(Message* message) {
    unsigned long index = message->plain_text.find(':');
    std::string ip = message->plain_text.substr(0, index);
    int port = atoi(message->plain_text.substr(index+1).c_str());
    Peer peer(serializer, ip, port);
    peers.emplace_back(peer);
}


void Node::parseSignOut(Message* message) {
    unsigned long index = message->plain_text.find(':');
    std::string ip = message->plain_text.substr(0, index);
    int port = atoi(message->plain_text.substr(index+1).c_str());
    Peer peer(serializer, ip, port);
    auto it = find(peers.begin(), peers.end(), peer);
}

bool Node::defaultCallback(Socket* socket, int port, Serializer* serializer, Node* node) {
    static Node::Message_action action[6] = {&Node::parseAskPeers, &Node::parseAnswerPeers, &Node::parseSignIn, &Node::parseSignOut, &Node::parseTransaction, &Node::parseBlock};
    std::string buffer;
    while(socket->read(buffer)) {
        if (buffer.length()) {
            auto start = std::chrono::high_resolution_clock::now();
            std::cout << "Request received on port " << port << " >> " << std::endl;
            Message *message = serializer->unserializeMessage(buffer, "json");
            (node->*(action[message->type]))(message);
            auto end = std::chrono::high_resolution_clock::now();
            long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
            std::cout << "Request performed in " << (microseconds / 1000.0) << " milliseconds" << std::endl;
        }
    }
    return true;
}