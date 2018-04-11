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

Hash::Hash(){
}

Element* Hash::toElement() {
    ElementObject* e = ElementCreator::creator.object();
    ElementCreator::creator.put(e, "hash", ElementCreator::creator.create(hash));
    return e;
}

void Hash::fromElement(ElementObject* e, const Serializer* serializer, const char* encoding) {
    e->getItem("hash", &hash);
}

