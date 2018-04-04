//
// Created by default on 4/4/2561.
//

#ifndef BLOCK_CHAIN_CUSTOM_VALIDATOR_H
#define BLOCK_CHAIN_CUSTOM_VALIDATOR_H

#include "../block_chain/Validator.h"

class CustomValidator: public Validator {
    bool operator()(Block* block);
};


#endif //BLOCK_CHAIN_CUSTOM_VALIDATOR_H
