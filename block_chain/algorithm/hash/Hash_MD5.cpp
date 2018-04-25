//
// Created by default on 3/4/2561.
//

#include "Hash_MD5.h"
#include <utility>
#include "../../utils/serialization/Serializer.h"


std::string Hash_MD5::generate_hash(const Component* component, const Serializer* serializer, const char* encoding){
    unsigned char digest[MD5_DIGEST_LENGTH + 1];
    std::string str = serializer->serialize(component, encoding);
    MD5((const unsigned char*) str.c_str(), str.size(), digest);
    digest[MD5_DIGEST_LENGTH] = 0;
    return Encoding::toHexa(std::string((const char*)digest));
}

std::string Hash_MD5::generate_hash(std::string hash1, std::string timestamp){
    unsigned char digest[MD5_DIGEST_LENGTH + 1];
    std::string str = hash1 + timestamp;
    MD5((const unsigned char*) str.c_str(), str.size(), digest);
    digest[MD5_DIGEST_LENGTH] = 0;
    return Encoding::toHexa(std::string((const char*)digest));
}

std::string Hash_MD5::generate_hash(std::string timestamp){
    unsigned char digest[MD5_DIGEST_LENGTH + 1];
    std::string str = timestamp;
    MD5((const unsigned char*) str.c_str(), str.size(), digest);
    digest[MD5_DIGEST_LENGTH] = 0;
    return Encoding::toHexa(std::string((const char*)digest));
}


std::string Hash_MD5::generate_hash(std::string hash1, double timestamp){
    unsigned char digest[MD5_DIGEST_LENGTH + 1];
    std::string str = hash1 + std::to_string(timestamp);
    MD5((const unsigned char*) str.c_str(), str.size(), digest);
    digest[MD5_DIGEST_LENGTH] = 0;
    return Encoding::toHexa(std::string((const char*)digest));
}

std::string Hash_MD5::generate_hash(std::string hash1, int timestamp){
    unsigned char digest[MD5_DIGEST_LENGTH + 1];
    std::string str = hash1 + std::to_string(timestamp);
    MD5((const unsigned char*) str.c_str(), str.size(), digest);
    digest[MD5_DIGEST_LENGTH] = 0;
    return Encoding::toHexa(std::string((const char*)digest));
}

std::string Hash_MD5::generate_hash(std::string hash1, long long int value){
    unsigned char digest[MD5_DIGEST_LENGTH + 1];
    std::string str = hash1 + std::to_string(value);
    MD5((const unsigned char*) str.c_str(), str.size(), digest);
    digest[MD5_DIGEST_LENGTH] = 0;
    return Encoding::toHexa(std::string((const char*)digest));
}

Hash_MD5::Hash_MD5() = default;
