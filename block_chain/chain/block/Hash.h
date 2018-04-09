//
// Created by default on 3/4/2561.
//

#ifndef BLOCK_CHAIN_HASH_H
#define BLOCK_CHAIN_HASH_H

#include <string>
#include <openssl/md5.h>
#include "transaction/Transaction.h"
#include "../../utils/Encoding.h"

class Serializer;
class Hash{
public:
    Hash(Component* component, Serializer* serializer, const char* encoding);
    std::string to_string() const;
    void set_hash(std::string str);
    bool operator==(Hash const& h) const{
        return hash == h.hash;
    }
private:
    std::string hash;
};

#endif //BLOCK_CHAIN_HASH_H
