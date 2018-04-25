//
// Created by default on 3/4/2561.
//

#ifndef BLOCK_CHAIN_HASH_MD5_H
#define BLOCK_CHAIN_HASH_MD5_H

#include <string>
#include <openssl/md5.h>
#include "../../kernel/components/Component.h"
#include "../../utils/Encoding.h"
#include "Hash.h"
#include <iostream>

class Serializer;

/**
 *  @class Hash_MD5 "block_chain/algorithm/hash/Hash_MD5.h"
 *  A class for md5 based hash, based on OpenSLL
 *
 *  @author Mathieu Lochet
 *  @version 3
 */
class Hash_MD5: public Hash{
public:

    /**
     *  A default constructor
     */
    Hash_MD5();

    std::string generate_hash(std::string hash1, double value) override;

    std::string generate_hash(std::string hash1, int value) override;

    std::string generate_hash(std::string hash1, long long int value) override;

    std::string generate_hash(std::string hash1, std::string value) override;

    std::string generate_hash(std::string value) override;

    std::string generate_hash(const Component* component, const Serializer* serializer, const char* encoding) override;
};

#endif //BLOCK_CHAIN_HASH_MD5_H
