//
// Created by default on 4/4/2561.
//

#include "CustomValidator.h"

bool CustomValidator::operator()(Transaction* transaction){
    return true;
}
bool CustomValidator::operator()(Block const& block){
    //TODO: I need to compute the Blocks fingerprint and check if it is equals to the provided fingerprint
    return true;
}