//
// Created by default on 17/4/2561.
//

#ifndef BLOCK_CHAIN_CHAIN_H
#define BLOCK_CHAIN_CHAIN_H


#include <vector>
#include "block/Hash.h"
#include "block/Block.h"
#include "Database.h"
#include "../Serializer.h"

class Chain {
    friend class NodeState;
public:
    Chain(Block*, Chain* c);
    Chain(Reward* r);
    ~Chain();
    void add(Block*);
    std::pair<int, Chain*> top_fingerprint();
    void update_database(Block*, const Serializer* s, const char* encoding);
    bool check_transaction(Transaction* transaction, std::string k);
    int count() const;
private:
    Database database;
    Hash* fingerprint;
    std::vector<Chain*> chain;

    void show();

    int find(Hash *pHash);

    Block * find(std::string str);
    Block *block;
};




#endif //BLOCK_CHAIN_CHAIN_H
