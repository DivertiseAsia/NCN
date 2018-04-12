//
// Created by default on 3/4/2561.
//
#ifndef BLOCK_CHAIN_CHAIN_H
#define BLOCK_CHAIN_CHAIN_H

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

class NodeState{
public:
    explicit NodeState(Serializer* s, int si = 64);
    Block* create_block() const;
    Block* add(std::string transaction, std::string public_key);
    void add(Block* block);
    void read_blocks();
    void clear_transactions();
    bool check_transaction(Transaction * transaction, std::string k);
private:
    unsigned int size;
    Hash* top_fingerprint;
    std::vector<std::pair<std::string, std::string>>  transactions;
    Serializer* serializer;
    Database database;
    void update_database(Block* block);
};
#endif //BLOCK_CHAIN_CHAIN_H
