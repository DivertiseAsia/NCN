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
#include "block/transaction/Transaction.h"

class Chain{
public:
    Chain(int s = 64);
    Block* create_block() const;
    Block* add(Transaction* transaction);
    void add(Block const& block);
    void read_blocks();
private:
    int size;
    Hash top;
    std::vector<Transaction*>  transactions;
};
#endif //BLOCK_CHAIN_CHAIN_H
