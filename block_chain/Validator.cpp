//
// Created by default on 3/4/2561.
//

#include "Validator.h"

Validator::Validator() = default;

//TODO: find a validation function
bool Validator::operator()(Transaction* transaction){
    return true;
}
bool Validator::operator()(Block const& block){
    //TODO: I need to compute the Blocks fingerprint and check if it is equals to the provided fingerprint
    return true;
}