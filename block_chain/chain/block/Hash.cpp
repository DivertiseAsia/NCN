//
// Created by default on 3/4/2561.
//

#include "Hash.h"
#include <utility>

std::string Hash::to_string() const {
    return hash;
}

void Hash::set_hash(std::string str) {
    hash = std::move(str);
}