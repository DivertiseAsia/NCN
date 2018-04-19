//
// Created by default on 3/4/2561.
//

#include "Hash.h"
#include <utility>
#include "../utils/serialization/Serializer.h"

std::string Hash::to_string() const {
    return hash;
}

Hash::Hash(const Component* component, const Serializer* serializer, const char* encoding){
    unsigned char digest[MD5_DIGEST_LENGTH + 1];
    std::string str = serializer->serialize(component, encoding);
    MD5((const unsigned char*) str.c_str(), str.size(), digest);
    digest[MD5_DIGEST_LENGTH] = 0;
    hash = Encoding::toHexa(std::string((const char*)digest));
}

Hash::Hash(Hash* hash1, Hash* hash2){
    unsigned char digest[MD5_DIGEST_LENGTH + 1];
    std::string str = hash1->hash + hash2->hash;
    MD5((const unsigned char*) str.c_str(), str.size(), digest);
    digest[MD5_DIGEST_LENGTH] = 0;
    hash = Encoding::toHexa(std::string((const char*)digest));
}

Hash::Hash(Hash* hash1, std::string timestamp){
    unsigned char digest[MD5_DIGEST_LENGTH + 1];
    std::string str = hash1->hash + timestamp;
    MD5((const unsigned char*) str.c_str(), str.size(), digest);
    digest[MD5_DIGEST_LENGTH] = 0;
    hash = Encoding::toHexa(std::string((const char*)digest));
}

Hash::Hash(std::string timestamp){
    unsigned char digest[MD5_DIGEST_LENGTH + 1];
    std::string str = timestamp;
    MD5((const unsigned char*) str.c_str(), str.size(), digest);
    digest[MD5_DIGEST_LENGTH] = 0;
    hash = Encoding::toHexa(std::string((const char*)digest));
}


Hash::Hash(Hash* hash1, double timestamp){
    unsigned char digest[MD5_DIGEST_LENGTH + 1];
    std::string str = hash1->hash + std::to_string(timestamp);
    MD5((const unsigned char*) str.c_str(), str.size(), digest);
    digest[MD5_DIGEST_LENGTH] = 0;
    hash = Encoding::toHexa(std::string((const char*)digest));
}

Hash::Hash(Hash* hash1, int timestamp){
    unsigned char digest[MD5_DIGEST_LENGTH + 1];
    std::string str = hash1->hash + std::to_string(timestamp);
    MD5((const unsigned char*) str.c_str(), str.size(), digest);
    digest[MD5_DIGEST_LENGTH] = 0;
    hash = Encoding::toHexa(std::string((const char*)digest));
}

Hash::Hash(Hash* hash1, long long int value){
    unsigned char digest[MD5_DIGEST_LENGTH + 1];
    std::string str = hash1->hash + std::to_string(value);
    MD5((const unsigned char*) str.c_str(), str.size(), digest);
    digest[MD5_DIGEST_LENGTH] = 0;
    hash = Encoding::toHexa(std::string((const char*)digest));
}

Hash::Hash() = default;

Element* Hash::toElement() {
    ElementObject* e = ElementCreator::object();
    return e->put("hash", ElementCreator::create(hash));
}

void Hash::fromElement(ElementObject* e, const Serializer*, const char*) {
    hash = "0";
    e->getItem("hash", &hash);
}
