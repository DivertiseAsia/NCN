//
// Created by default on 3/4/2561.
//

#include "Node.h"

void run(SocketServer* server, Serializer* serializer, Node* node) {
    server->run(Node::defaultCallback, serializer, node);
}
Node::Node(Serializer* s, int p): serializer(s), validator(serializer, "json"), block_chain(s, 1), server(p), running(run, &server, s, this), self(serializer, Socket::getIP(), p) {


    OpenSSL_add_all_algorithms();
    ERR_load_BIO_strings();
    ERR_load_crypto_strings();
    if(!rsa.backup("./network/private..pem", "./network/public..pem"))
        rsa.generate("./network/private.pem", "./network/public.pem");
    store(Socket::getIP(), p);
    running.detach();
    if(peers.size() == 0)
        block_chain.read_blocks();
}

Node::~Node(){
    std::cout<< "Closing connection" <<std::endl;
    server.close();
    #ifndef _WIN32
    running.detach();
    #endif // _WIN32
    close();
    delete serializer;
    std::this_thread::sleep_for(std::chrono::microseconds(1000000));
    std::cout<< "Connection closed" <<std::endl;
}

void Node::load(std::string l){
    Message message(self.to_string(), "", "", nullptr, Message::SIGN_IN);
    char* m = serializer->serialize(&message, "json");
    std::istringstream list(l);
    std::string line;
    while (std::getline (list, line)) {
        unsigned long index = line.find(':');
        std::string ip = line.substr(0, index);
        int port = atoi(line.substr(index+1).c_str());
        Peer peer(serializer, ip, port);
        peers.emplace_back(peer);
        peer.send(Encoding::toHexa(std::string(m)).c_str());
    }
    free(m);
    if(peers.size() == 1)
        block_chain.read_blocks();
}

void Node::store(std::string _ip, int _p){
    std::ifstream peers_file;
    int i = 0;
    peers_file.open("./network/network.nfo", std::ifstream::in);
    if(peers_file.is_open()){
        std::string line;
        Message message(self.to_string(), "", "", nullptr, Message::ASK_PEERS);
        char* m = serializer->serialize(&message, "json");
        while (std::getline (peers_file, line)) {
            unsigned long index = line.find(':');
            std::string ip = line.substr(0, index);
            int port = atoi(line.substr(index+1).c_str());
            if(_ip != ip || _p != port){
                Peer peer(serializer, ip, port);
                if(peer.send(Encoding::toHexa(std::string(m)).c_str())) {
                    i = 1;
                    break;
                }
            }
        }
        peers_file.close();
        free(m);
    }
    if(!i)
        block_chain.read_blocks();
    /*
    */
}
void Node::close(){
    Message message(self.to_string(), "", "", nullptr, Message::SIGN_OUT);
    char* m = serializer->serialize(&message, "json");
    for (auto &peer : peers)
            peer.send(Encoding::toHexa(std::string(m)).c_str());
    free(m);
}

void Node::request_transaction(Transaction* transaction){
    MerkleTree tree(transaction, serializer, "json");
    const char* serialized = serializer->serialize(transaction, "json");
    Message message(serialized, rsa.encrypt(serialized), rsa.getPublicKey(), &tree, Message::TRANSACTION);
    char* m = serializer->serialize(&message, "json");
    Encoding::toHexa(std::string(m));
    for (auto &peer : peers)
        peer.send(Encoding::toHexa(std::string(m)).c_str());
    free(m);
}

bool Node::operator()(Transaction* transaction, Message* message) {
    bool valid = (*message->tree->value == *transaction->__hash__(serializer, "json") && block_chain.check_transaction(transaction, message->public_key));
    if(valid) {
        Block *block = block_chain.add(message->cipher, Encoding::toHexa(message->public_key));
        //TODO: generate proof of something
        if(block != nullptr){
            std::vector<Transaction*> transactions;
            for(auto& t : block->transactions){
                std::string cipher(Encoding::fromHexa(t.first));
                RSA_Cryptography crypto(Encoding::fromHexa(t.second));
                transactions.emplace_back(serializer->unserializeTransaction(crypto.decrypt(cipher, cipher.size()), "json"));
            }
            std::string serialized_block(serializer->serialize(block, "json"));
            MerkleTree tree(transactions, serializer, "json");
            Message message(serialized_block, "",""/*rsa.encrypt(serialized_block), rsa.getPublicKey()*/, &tree, Message::BLOCK);
            char* m = serializer->serialize(&message, "json");
            for (auto &peer : peers)
                peer.send(Encoding::toHexa(std::string(m)).c_str());
            free(m);
        }
    }
    return valid;
}
bool Node::operator()(Block* block, Message* message) {
    if(validator(block))
    {
        int i = 0;
        //TODO: tests necessaires
        for(auto& t : block->transactions){
            std::string cipher(Encoding::fromHexa(t.first));
            RSA_Cryptography crypto(Encoding::fromHexa(t.second));
            Transaction* transaction = serializer->unserializeTransaction(crypto.decrypt(cipher, cipher.size()), "json");
            bool valid = *message->tree->get_hash(i) == *transaction->__hash__(serializer, "json");
            std::cout << "<" << valid << ">" <<std::endl;
            if(!valid)
                return false;
            i++;
        }
        block_chain.add(block);
        block_chain.clear_transactions();
        return true;
    }
    return false;
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
    std::string peers_to_send(self.to_string());
    for (auto &peer : peers)
        peers_to_send += peer.to_string() + std::string("\n");
    message->plain_text = peers_to_send;
    message->type = Message::ANSWER_PEERS;
    char* m = serializer->serialize(message, "json");
    peer.send(Encoding::toHexa(std::string(m)).c_str());
    peers.emplace_back(peer);
    free(m);
}

void Node::parseTransaction(Message* message){
    RSA_Cryptography crypto(message->public_key);
    std::string str(message->getCipher());
    Transaction* deciphered(serializer->unserializeTransaction(crypto.decrypt(str, (int)str.size()), "json"));
    Transaction* plain_text(serializer->unserializeTransaction(message->plain_text, "json"));
    if(*deciphered == plain_text)
        (*this)(plain_text, message);
    else
        delete plain_text;
    delete deciphered;
}

void Node::parseBlock(Message* message) {
    RSA_Cryptography crypto(message->public_key);
    //std::string str(message->getCipher());
    //Block* deciphered(serializer->unserializeBlock(crypto.decrypt(str, (int)str.size()), "json"));
    Block* plain_text(serializer->unserializeBlock(message->plain_text, "json"));
    //if(*deciphered == plain_text)
    (*this)(plain_text, message);
    //else
    //    delete plain_text;
    //delete deciphered;
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
    if(it != peers.end()) {
        it->close();
        peers.erase(it);
    }
}

bool Node::defaultCallback(Socket* socket, int port, Serializer* serializer, Node* node) {
    static Node::Message_action action[6] = {&Node::parseAskPeers, &Node::parseAnswerPeers, &Node::parseSignIn, &Node::parseSignOut, &Node::parseTransaction, &Node::parseBlock};
    std::string buffer;
    //socket->read(buffer);
    while(socket->read(buffer)) {
        if (buffer.length()) {
            auto start = std::chrono::high_resolution_clock::now();
            std::cout << "Request received on port " << port << " >> ";
            buffer = Encoding::fromHexa(buffer.c_str());
            std::cout << buffer << std::endl;
            Message *message = serializer->unserializeMessage(buffer, "json");
            (node->*(action[message->type]))(message);
            auto end = std::chrono::high_resolution_clock::now();
            long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
            std::cout << "Request performed in " << (microseconds / 1000.0) << " milliseconds" << std::endl;
        }
    }
    return true;
}
