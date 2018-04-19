//
// Created by default on 12/4/2561.
//

#ifndef BLOCK_CHAIN_PROOFOFSTAKETIME_H
#define BLOCK_CHAIN_PROOFOFSTAKETIME_H


#include "Proof.h"

class ProofOfStakeTime: public Proof {
public:
    void run(Block* block, std::string key) override;
    bool accept(Block* block, Message* message) override;
};



#endif //BLOCK_CHAIN_PROOFOFSTAKETIME_H
