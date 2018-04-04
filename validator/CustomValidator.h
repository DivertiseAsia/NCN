//
// Created by default on 4/4/2561.
//

#ifndef BLOCK_CHAIN_CUSTOMVALIDATOR_H
#define BLOCK_CHAIN_CUSTOMVALIDATOR_H

#include "../block_chain/Validator.h"

class CustomValidator: public Validator {
    virtual bool operator()(Block const& block);
};


#endif //BLOCK_CHAIN_CUSTOMVALIDATOR_H
