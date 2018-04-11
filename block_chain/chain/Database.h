//
// Created by default on 11/4/2561.
//

#ifndef BLOCK_CHAIN_DATABASE_H
#define BLOCK_CHAIN_DATABASE_H

#include <map>
#include <string>
#include "Row.h"

class Database {
    friend class NodeState;
private:
    std::map<std::string, Row*> rows;
};


#endif //BLOCK_CHAIN_DATABASE_H
