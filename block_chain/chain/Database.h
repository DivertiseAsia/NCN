//
// Created by default on 11/4/2561.
//

#ifndef BLOCK_CHAIN_DATABASE_H
#define BLOCK_CHAIN_DATABASE_H

#include <map>
#include <string>
#include "Row.h"

class Database {
    friend class Chain;
public:
    void operator=(Database const& d){
        for(auto& r : d.rows){
            this->rows[r.first] = r.second->clone();
        }
    }

    Row *get(std::string basic_string);

private:
    std::map<std::string, Row*> rows;
};


#endif //BLOCK_CHAIN_DATABASE_H
