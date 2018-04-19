//
// Created by default on 11/4/2561.
//

#ifndef BLOCK_CHAIN_DATABASE_H
#define BLOCK_CHAIN_DATABASE_H

#include <map>
#include <string>
#include "Row.h"
#include "../block/transaction/Transaction.h"
#include "../block/transaction/Reward.h"

class Database {
    friend class Chain;
public:
    explicit Database(Reward* r): reward_transaction(r) {
    }
    Database& operator=(Database const& d){
        for(auto& r : d.rows){
            this->rows[r.first] = r.second->clone();
        }
        reward_transaction = d.reward_transaction;
        return *this;
    }
    Row *get(std::string key) {
        auto a = rows.find(key);
        if(a == rows.end())
            return nullptr;
        return a->second;
    }


    Row* reward(std::string winner)
    {
        Row* r = this->get(winner);
        if(r == nullptr && reward_transaction){
            r = reward_transaction->createRow();
            rows[winner] = r;
        }
        return r;
    }

private:
    std::map<std::string, Row*> rows;
    Reward* reward_transaction;
};


#endif //BLOCK_CHAIN_DATABASE_H