//
// Created by default on 3/4/2561.
//

#include "Hash.h"
#include <utility>
#include "../../Serializer.h"

std::string Hash::to_string() const {
    return hash;
}

void Hash::set_hash(std::string str) {
    hash = std::move(str);
}

Hash::Hash(Component* component, Serializer* serializer, const char* encoding){
    unsigned char digest[MD5_DIGEST_LENGTH];
    std::string str = serializer->serialize(component, encoding);
    const unsigned char* c = MD5((const unsigned char*) str.c_str(), str.size(), digest);
    hash = Encoding::toHexa(std::string((const char*)c));
}
