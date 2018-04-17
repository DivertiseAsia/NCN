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
#include "block/Block.h"
#include "block/Hash.h"
#include "block/transaction/TransactionContainer.h"
#include "../Serializer.h"
#include "Database.h"
#include "Chain.h"

class NodeState{
public:
    explicit NodeState(Serializer* s, int si = 64, const char* e = "json");
    Block* create_block() const;
    Block* add(std::string transaction, std::string public_key);
    void add(Block* block);
    void read_blocks();
    void clear_transactions();
    bool check_transaction(Transaction * transaction, std::string k);
private:
    std::string encoding;
    unsigned int size;
    Chain* chain;
    std::vector<std::pair<std::string, std::string>>  transactions;
    Serializer* serializer;
    void update_database(Block* block);
};
#endif //BLOCK_NODE_STATE_CHAIN_H
