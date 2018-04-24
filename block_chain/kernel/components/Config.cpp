//
// Created by default on 24/4/2561.
//

#include "Config.h"


ElementObject* read_config(const char* filename, Serializer* serial, const char* encoding){
    std::ifstream block_file(filename);
    std::string line;
    std::string serialized;
    if(block_file.is_open()){
        while (std::getline (block_file, line))
            serialized += line;
    }
    return serial->getElement(serialized, encoding);
}

Config::Config(const char* filename, Serializer* s, int pr, Reward* r): serializer(s), reward(r), proof(Proof::generate(pr)){
    ElementObject* o = read_config(filename, s, "json");
    o->getItem("port", &port);
    o->getItem("encoding", &encoding);
    o->getItem("debug", &debug);
}

const char* Config::get_encoding() const{
    return encoding.c_str();
}

const Serializer* Config::get_serializer() const{
    return serializer;
}

const Proof* Config::get_proof() const{
    return proof;
}

const Reward* Config::get_reward() const{
    return reward;
}

const int Config::get_port() const{
    return port;
}

const bool Config::is_debug() const{
    return debug;
}