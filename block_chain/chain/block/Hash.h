//
// Created by default on 3/4/2561.
//

#ifndef BLOCK_CHAIN_HASH_H
#define BLOCK_CHAIN_HASH_H

#include <string>
class Hash{
public:
    std::string to_string() const;
    void set_hash(std::string str);
private:
    std::string hash;
};

#endif //BLOCK_CHAIN_HASH_H
