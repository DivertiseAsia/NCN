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

struct HashCompare
{
    bool operator() (const Hash& hash1, const Hash& hash2) const
    {
        return true;
    }
};
#endif //BLOCK_CHAIN_HASH_H
