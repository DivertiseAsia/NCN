//
// Created by default on 3/4/2561.
//

#ifndef BLOCK_CHAIN_BLOCK_H
#define BLOCK_CHAIN_BLOCK_H

#include <vector>
#include "Hash.h"
#include "Metadata.h"
#include "transaction/Transaction.h"

class Block{
    friend class Chain;
public:
    Block();
    explicit Block(std::vector<Transaction*> transactions);
private:
    Metadata data;
    Hash hash;
    Hash parent_hash;
};
#endif //BLOCK_CHAIN_BLOCK_H
