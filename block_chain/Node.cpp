//
// Created by default on 3/4/2561.
//

#include "Node.h"

void run(SocketServer* server, const Serializer* serializer, Node* node) {
    server->run(Node::defaultCallback, serializer, node);
}
Node::Node(Config& config): serializer(config.get_serializer()), encoding(config.get_encoding()), proof(config.get_proof()), server(config.get_port()), block_chain(serializer, 1, encoding.c_str(), config.get_reward()), self(Socket::getIP(), config.get_port()), running(run, &server, serializer, this), queue(0), debug(config.is_debug()) {
    init_parsers();
    OpenSSL_add_all_algorithms();
    ERR_load_BIO_strings();
    ERR_load_crypto_strings();
    if(!rsa.backup("./network/private.pem", "./network/public.pem"))
        rsa.generate("./network/private.pem", "./network/public.pem");
    store();
    block_chain.read_blocks();
}

void Node::init_parsers(){
    add_parser(new BlockAnswerParser);
    add_parser(new BlockAskParser);
    add_parser(new PeersAnswerParser);
    add_parser(new PeersAskParser);
    add_parser(new SignInParser);
    add_parser(new SignOutParser);
    add_parser(new TransactionParser);
    add_parser(new BlockParser);
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

void Node::add_parser(MessageParser* p){
    parsers[p->get_type()] = p;
}

void Node::store(){
    std::ifstream peers_file;
    int i = 0;
    peers_file.open("./network/network.nfo", std::ifstream::in);
    if(peers_file.is_open()){
        std::string line;
        AskPeersMessage message(self.to_string());
        char* m = serializer->serialize(&message, encoding.c_str());
        while (std::getline (peers_file, line)) {
            unsigned long index = line.find(':');
            std::string ip = line.substr(0, index);
            int port = atoi(line.substr(index+1).c_str());
            if(self._ip != ip || self._port != port){
                Peer peer(ip, port);
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
    SignOutMessage message(self.to_string());
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
    TransactionMessage message(serialized, rsa.encrypt(serialized), rsa.getPublicKey(), &tree);
    char* m = serializer->serialize(&message, encoding.c_str());
    Encoding::toHexa(std::string(m));
    for (auto &peer : peers)
        peer.send(Encoding::toHexa(std::string(m)).c_str());
    self.send(Encoding::toHexa(std::string(m)).c_str());
    free(m);
}

int Node::load(Block *pBlock) {
    if(!block_chain.get(pBlock->parent_fingerprint)){
        if(!peers.empty()) {
            srand(time(NULL));
            BlockAskMessage answer(self.to_string(), pBlock->parent_fingerprint->to_string());
            char* m = serializer->serialize(&answer, encoding.c_str());
            int index = (int) (rand() % peers.size());
            peers[index].send(Encoding::toHexa(m).c_str());
            waiting.emplace(waiting.begin(), pBlock);
            free(m);
        }
        return 0;
    }
    return 1;
}

void Node::async(Message* message, Node* node){
    auto start = std::chrono::high_resolution_clock::now();
    (*node->parsers.find(message->get_type())->second)(message, node);
    auto end = std::chrono::high_resolution_clock::now();
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    if(node->debug)
        std::cout << "\033[1;36m[RECV] Request performed in " << (microseconds / 1000.0) << " milliseconds\033[0m\n";
    delete message;
}

bool Node::defaultCallback(Socket* socket, int port, const Serializer* serializer, Node* node) {
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
    for(auto& a : threads) {
        a->join();
        delete a;
    }
    return true;
}

void Node::start(TransactionManager manager) {
    Transaction* t = nullptr;
    do {
        t = manager.run();
        if((long long int)t == -1)
            block_chain.show_current_state();
        else if(t)
            request_transaction(t);
    }
    while(t != nullptr);
}
