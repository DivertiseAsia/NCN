//
// Created by default on 25/4/2561.
//

#include "Cryptography.h"
#include "RSA.h"

const int Cryptography::CRYPTOGRAPHY_RSA = 0;
std::map<int, std::function<Cryptography*()>> Cryptography::cryptography;

Cryptography* Cryptography::generate(const int type) {
    if(cryptography.empty()) {
        cryptography[Cryptography::CRYPTOGRAPHY_RSA] = []() -> Cryptography*{return new RSA_Cryptography;};
    }
    return (cryptography.find(type)->second)();
}

Cryptography* Cryptography::generate(const int type, std::string key) {
    Cryptography* c = generate(type);
    c->set_public_key(std::move(key));
    return c;
}

void Cryptography::add_cryptography(int id, std::function<Cryptography *()> h) {
    cryptography[id] = std::move(h);
}
