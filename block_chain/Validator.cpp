//
// Created by default on 3/4/2561.
//

#include "Validator.h"

Validator::Validator() = default;

bool Validator::operator()(Transaction* transaction){
    return (*transaction)();
}
bool Validator::operator()(Block* block){
    return true;
}

Validator::~Validator(){
}
