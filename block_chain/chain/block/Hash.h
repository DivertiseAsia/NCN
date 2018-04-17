//
// Created by default on 3/4/2561.
//

#ifndef BLOCK_CHAIN_HASH_H
#define BLOCK_CHAIN_HASH_H

#include <string>
#include <openssl/md5.h>
#include "Component.h"
#include "../../utils/Encoding.h"
#include <iostream>

class Serializer;
class Hash{
public:
    Hash();
    Hash(Hash* hash1, Hash* hash2);
    Hash(Hash* hash1, double timestamp);
    Hash(Hash* hash1, int timestamp);
    Hash(Hash* hash1, unsigned long long int timestamp);
    Hash(const Component* component, const Serializer* serializer, const char* encoding);
    std::string to_string() const;
    bool operator==(Hash const& h) const{
        return hash == h.hash;
    }
    Element* toElement();
    void fromElement(ElementObject* e, const Serializer* serializer, const char* encoding);
    std::string hash;
private:
};

#endif //BLOCK_CHAIN_HASH_H
