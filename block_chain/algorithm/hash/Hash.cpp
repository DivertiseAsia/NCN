//
// Created by default on 25/4/2561.
//

#include "Hash.h"
//
// Created by default on 3/4/2561.
//

#include <utility>
#include "../../utils/serialization/Serializer.h"

const int Hash::HASH_MD5 = 0;
std::map<int, std::function<Hash*()>> Hash::hash;

Hash* Hash::HASH = nullptr;

Hash::Hash() = default;

Hash* Hash::get_hash(){
    return Hash::HASH;
}

void Hash::set_hash(Hash* h) {
    Hash::HASH = h;
}

Hash* Hash::generate(const int type) {
    if(hash.empty()) {
        hash[Hash::HASH_MD5] = []() -> Hash*{return new Hash_MD5;};
    }
    return (hash.find(type)->second)();
}

void Hash::add_hash(int id, std::function<Hash *()> h) {
    hash[id] = std::move(h);
}
