//
// Created by default on 3/4/2561.
//
#ifndef BLOCK_NODE_STATE_CHAIN_H
#define BLOCK_NODE_STATE_CHAIN_H

#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sys/stat.h>
#include <dirent.h>
#include <algorithm>
#include <utility>
#include "block/Block.h"
#include "state/Database.h"
#include "Chain.h"
#include "../algorithm/Hash.h"
#include "../algorithm/RSA.h"
#include "../utils/serialization/Serializer.h"
#include "../utils/socket/Peer.h"

class NodeState{
public:
    explicit NodeState(Serializer* s, int si = 64, const char* e = "json", Reward* r = nullptr);
    Block* create_block() const;
    Block* add(std::string transaction, std::string public_key);
    void add(Block* block);
    void read_blocks();
    bool check_transaction(Transaction * transaction, std::string k);
    void show_current_state();
    bool get(Hash *pHash);
    Block *get(std::string hash);

private:
    std::string encoding;
    unsigned int size;
    Chain* chain;
    std::vector<std::pair<std::string, std::string>>  transactions;
    Serializer* serializer;
    void update_database(Block* block);

};
#endif //BLOCK_NODE_STATE_CHAIN_H
