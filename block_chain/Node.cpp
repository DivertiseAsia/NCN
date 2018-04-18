//
// Created by default on 3/4/2561.
//

#include "Node.h"

void run(SocketServer* server, Serializer* serializer, Node* node) {
    server->run(Node::defaultCallback, serializer, node);
}
Node::Node(Serializer* s, int p, const char* e, int pr, bool d): queue(0), serializer(s), encoding(e), proof(Proof::generate(pr)), validator(serializer, encoding.c_str()), block_chain(s, 1), server(p), running(run, &server, s, this), self(serializer, Socket::getIP(), p), debug(d) {
    OpenSSL_add_all_algorithms();
    ERR_load_BIO_strings();
    ERR_load_crypto_strings();
    if(!rsa.backup("./network/private.pem", "./network/public.pem"))
        rsa.generate("./network/private.pem", "./network/public.pem");
    store(Socket::getIP(), p);
    block_chain.read_blocks();
}

Node::~Node(){
    std::cout<< "Closing connection" <<std::endl;
    close();
    std::this_thread::sleep_for(std::chrono::microseconds(1000000));
    server.close();
    delete proof;
    #ifndef _WIN32
    running.detach();
    #endif // _WIN32
    delete serializer;
    std::this_thread::sleep_for(std::chrono::microseconds(1000000));
    std::cout<< "Connection closed" <<std::endl;
}

void Node::load(std::string l){
    Message message(self.to_string(), "", "", nullptr, Message::SIGN_IN);
    char* m = serializer->serialize(&message, encoding.c_str());
    std::istringstream list(l);
    std::string line;
    while (std::getline (list, line)) {
        unsigned long index = line.find(':');
        std::string ip = line.substr(0, index);
        int port = atoi(line.substr(index+1).c_str());
        if(ip != self._ip || port != self._port) {
            Peer peer(serializer, ip, port);
            peers.emplace_back(peer);
            peer.send(Encoding::toHexa(std::string(m)).c_str());
        }
    }
    free(m);
}

void Node::store(std::string _ip, int _p){
    std::ifstream peers_file;
    int i = 0;
    peers_file.open("./network/network.nfo", std::ifstream::in);
    if(peers_file.is_open()){
        std::string line;
        Message message(self.to_string(), "", "", nullptr, Message::ASK_PEERS);
        char* m = serializer->serialize(&message, encoding.c_str());
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
}
void Node::close(){
    Message message(self.to_string(), "", "", nullptr, Message::SIGN_OUT);
    char* m = serializer->serialize(&message, encoding.c_str());
    for (auto &peer : peers)
        peer.send(Encoding::toHexa(std::string(m)).c_str());
    free(m);
}

void Node::request_transaction(Transaction* transaction){
    if(debug)
        std::cout << "\033[1;34m[INFO] Transaction requested by " << self._ip << ":" << self._port<<"\033[0m\n";
    MerkleTree tree(transaction, serializer, encoding.c_str());
    const char* serialized = serializer->serialize(transaction, encoding.c_str());
    Message message(serialized, rsa.encrypt(serialized), rsa.getPublicKey(), &tree, Message::TRANSACTION);
    char* m = serializer->serialize(&message, encoding.c_str());
    Encoding::toHexa(std::string(m));
    for (auto &peer : peers)
        peer.send(Encoding::toHexa(std::string(m)).c_str());
    self.send(Encoding::toHexa(std::string(m)).c_str());
    free(m);
}

bool Node::operator()(Transaction* transaction, Message* message) {
    if(debug)
        std::cout << "\033[1;32m[INFO] Transaction computed by " << self._ip << ":" << self._port<<"\033[0m\n";
    bool valid = (*message->tree->value == *transaction->__hash__(serializer, encoding.c_str()) && block_chain.check_transaction(transaction, message->public_key));
    if(valid) {
        Block *block = block_chain.add(message->cipher, Encoding::toHexa(message->public_key));
        if(block != nullptr){
            queue++;
            proof->run(block, message);
            block->update_fingerprint();
            std::vector<Transaction*> transactions;
            for(auto& t : block->transactions){
                std::string cipher(Encoding::fromHexa(t.first));
                RSA_Cryptography crypto(Encoding::fromHexa(t.second));
                transactions.emplace_back(serializer->unserializeTransaction(crypto.decrypt(cipher, cipher.size()), encoding.c_str()));
            }
            std::string serialized_block(serializer->serialize(block, encoding.c_str()));
            MerkleTree tree(transactions, serializer, encoding.c_str());
            Message answer(serialized_block, "",rsa.getPublicKey()/*rsa.encrypt(serialized_block), */, &tree, Message::BLOCK);
            char* m = serializer->serialize(&answer, encoding.c_str());
            if(queue > 0) {
                for (auto &peer : peers)
                    peer.send(Encoding::toHexa(std::string(m)).c_str());
                std::cout << "Generated: " << block->fingerprint->hash << std::endl;
                self.send(Encoding::toHexa(std::string(m)).c_str());
            }
            free(m);
        }
    }
    return valid;
}

int Node::load(Block *pBlock) {
    if(!block_chain.get(pBlock->parent_fingerprint)){
        if(!peers.empty()) {
            srand(time(NULL));
            Message answer(self.to_string(), pBlock->parent_fingerprint->hash, ""/*rsa.encrypt(serialized_block), */, nullptr, Message::ASK_BLOCK);
            char* m = serializer->serialize(&answer, encoding.c_str());
            peers[rand() % peers.size()].send(m);
            waiting.emplace(waiting.begin(), pBlock);
            free(m);
        }
        return 0;
    }
    return 1;
}

bool Node::operator()(Block* block, Message* message) {
    if(debug)
        std::cout << "\033[1;32m[INFO] Block computed by " << self._ip << ":" << self._port<<"\033[0m\n";
    if(load(block) && validator(block))
    {
        if(debug)
            std::cout << "\033[1;32m[INFO] Block accepted\033[0m\n";
        if(proof->accept(block, message)) {
            int i = 0;
            for (auto &t : block->transactions) {
                std::string cipher(Encoding::fromHexa(t.first));
                RSA_Cryptography crypto(Encoding::fromHexa(t.second));
                Transaction *transaction = serializer->unserializeTransaction(crypto.decrypt(cipher, cipher.size()), encoding.c_str());
                bool valid = *message->tree->get_hash(i) == *transaction->__hash__(serializer, encoding.c_str());
                if (!valid)
                    return false;
                i++;
            }
            if(debug)
                std::cout << "\033[1;32m[INFO] New Block\033[0m\n";
            queue--;
            std::cout << "Received: " << block->fingerprint->hash << std::endl;
            if(queue < 0)
                queue = 0;
            block_chain.add(block);
            return true;
        }
        else if(debug)
            std::cout << "\033[1;32m[INFO] Invalid proof\033[0m\n";
    }
    else if(debug)
        std::cout << "\033[1;32m[INFO] Invalid validator\033[0m\n";
    return false;
}

bool Node::operator()(Message*) {
    bool valid = true;
    return valid;
}

void Node::parseAnswerBlock(Message* message) {
    if(debug)
        std::cout << "\033[1;34m[INFO] Block Received by " << self._ip << ":" << self._port<<"\033[0m\n";
    Block *b(serializer->unserializeBlock(message->plain_text, encoding.c_str()));
    if (load(b)) {
        for (auto &a : waiting)
            block_chain.add(a);
        waiting.clear();
    }
}

void Node::parseAskBlock(Message* message){
    unsigned long index = message->plain_text.find(':');
    std::string ip = message->plain_text.substr(0, index);
    int port = atoi(message->plain_text.substr(index+1).c_str());
    if(debug)
        std::cout << "\033[1;34m[INFO] Block "<< Encoding::fromHexa(message->cipher) << " asked by " << self._ip << ":" << self._port<<"\033[0m\n";
    std::string hash = Encoding::fromHexa(message->cipher);
    Block* b = block_chain.get(hash);
    std::string serialized_block(serializer->serialize(b, encoding.c_str()));
    Message answer(serialized_block, "", "", nullptr, Message::ANSWER_BLOCK);
    char* m = serializer->serialize(&answer, encoding.c_str());
    Peer peer(serializer, ip, port);
    peer.send(Encoding::toHexa(std::string(m)).c_str());
    free(m);
}

void Node::parseAnswerPeers(Message* message) {
    if(debug)
        std::cout << "\033[1;34m[INFO] Peers received by " << self._ip << ":" << self._port<<"\033[0m\n";
    load(message->plain_text);
    block_chain.read_blocks();
}

void Node::parseAskPeers(Message* message) {
    unsigned long index = message->plain_text.find(':');
    std::string ip = message->plain_text.substr(0, index);
    int port = atoi(message->plain_text.substr(index+1).c_str());
    if(debug)
        std::cout << "\033[1;34m[INFO] Peers asked by " << ip << ":" << port<<"\033[0m\n";
    Peer peer(serializer, ip, port);
    std::string peers_to_send(self.to_string());
    for (auto &p : peers)
        peers_to_send += "\n" + p.to_string();
    message->plain_text = peers_to_send;
    message->type = Message::ANSWER_PEERS;
    char* m = serializer->serialize(message, encoding.c_str());
    peer.send(Encoding::toHexa(std::string(m)).c_str());
    free(m);
}

void Node::parseTransaction(Message* message){
    if(debug)
        std::cout << "\033[1;32m[INFO] Transaction parsed by " << self._ip << ":" << self._port<<"\033[0m\n";
    RSA_Cryptography crypto(message->public_key);
    std::string str(message->getCipher());
    Transaction* deciphered(serializer->unserializeTransaction(crypto.decrypt(str, (int)str.size()), encoding.c_str()));
    Transaction* plain_text(serializer->unserializeTransaction(message->plain_text, encoding.c_str()));
    if(*deciphered == plain_text)
        (*this)(plain_text, message);
    else
        delete plain_text;
    delete deciphered;
}

void Node::parseBlock(Message* message) {
    if(debug)
        std::cout << "\033[1;32m[INFO] Block parsed by " << self._ip << ":" << self._port<<"\033[0m\n";
    RSA_Cryptography crypto(message->public_key);
    Block* plain_text(serializer->unserializeBlock(message->plain_text, encoding.c_str()));
    (*this)(plain_text, message);
}

void Node::parseSignIn(Message* message) {
    unsigned long index = message->plain_text.find(':');
    std::string ip = message->plain_text.substr(0, index);
    int port = atoi(message->plain_text.substr(index+1).c_str());
    if(debug)
        std::cout << "\033[1;34m[IN] " << ip << ":" << port << " is signing in in " << self._ip << ":" << self._port<<"\033[0m\n";
    Peer peer(serializer, ip, port);
    peers.emplace_back(peer);
}


void Node::parseSignOut(Message* message) {
    unsigned long index = message->plain_text.find(':');
    std::string ip = message->plain_text.substr(0, index);
    int port = atoi(message->plain_text.substr(index+1).c_str());
    if(debug)
        std::cout << "\033[1;34m[OUT] " << ip << ":" << port << " is signing out from " << self._ip << ":" << self._port<<"\033[0m\n";
    Peer peer(serializer, ip, port);
    auto it = find(peers.begin(), peers.end(), peer);
    if(it != peers.end()) {
        it->close();
        peers.erase(it);
    }
}

void Node::async(Message* message, Node* node){
    static Node::Message_action action[8] = {&Node::parseAskPeers, &Node::parseAnswerPeers, &Node::parseSignIn, &Node::parseSignOut, &Node::parseTransaction, &Node::parseBlock, &Node::parseAskBlock, &Node::parseAnswerBlock};
    auto start = std::chrono::high_resolution_clock::now();
    (node->*(action[message->type]))(message);
    auto end = std::chrono::high_resolution_clock::now();
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    if(node->debug)
        std::cout << "\033[1;36m[RECV] Request performed in " << (microseconds / 1000.0) << " milliseconds\033[0m\n";
}

bool Node::defaultCallback(Socket* socket, int port, Serializer* serializer, Node* node) {
    std::string buffer;
    std::vector<std::thread*> threads;
    while(socket->read(buffer)) {
        if (buffer.length()) {
            buffer = Encoding::fromHexa(buffer);
            if(node->debug)
                std::cout << "\033[1;36m[RECV] Request received on port " << port << " >> " << buffer << "\033[0m\n";
            Message *message = serializer->unserializeMessage(buffer, node->encoding.c_str());
            threads.emplace_back(new std::thread(async, message, node));
        }
    }
    for(auto& a : threads)
        a->join();
    return true;
}

void Node::start(TransactionManager manager) {
    Transaction* t = nullptr;
    do{
        t = manager.run();
        if((long long int)t == -1){
            block_chain.show_current_state();
        }
        else if(t)
            request_transaction(t);
    }while(t != nullptr);
}
