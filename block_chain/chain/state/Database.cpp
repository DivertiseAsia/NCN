//
// Created by default on 11/4/2561.
//

#include "Database.h"

Database::Database(Database const& d){
    for(auto& r : d.rows){
    this->rows[r.first] = r.second->clone();
    }
    reward_transaction = d.reward_transaction;
}

Database::Database(Reward* r): reward_transaction(r) {
}

Row* Database::get(std::string key) {
    auto a = rows.find(key);
    if(a == rows.end())
        return nullptr;
    return a->second;
}

Row* Database::reward(std::string winner)
{
    Row* r = this->get(winner);
    if(r == nullptr && reward_transaction){
        r = reward_transaction->createRow();
        rows[winner] = r;
    }
    return r;
}