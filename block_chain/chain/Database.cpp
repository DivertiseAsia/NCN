//
// Created by default on 11/4/2561.
//

#include "Database.h"

Row *Database::get(std::string key) {
    auto a = rows.find(key);
    if(a == rows.end())
        return nullptr;
    return a->second;
}