//
// Created by default on 3/4/2561.
//

#include "Validator.h"
Validator::Validator(const Serializer* s, const char* e): serializer(s), encoding(e) {

}

bool Validator::operator()(Transaction* transaction){
    return (*transaction)();
}
bool Validator::operator()(TransactionContainer* transaction){
    return (*transaction)();
}
bool Validator::operator()(Block* block){
    return block->checkFingerPrint(serializer, encoding);
}

Validator::~Validator() = default;
