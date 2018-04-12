//
// Created by default on 12/4/2561.
//

#ifndef BLOCK_CHAIN_PROOFOFSTAKETIME_H
#define BLOCK_CHAIN_PROOFOFSTAKETIME_H


#include "Proof.h"

class ProofOfStakeTime: public Proof {
public:
    void run(Block* block) override;
    bool accept(Block* block) override;
};



#endif //BLOCK_CHAIN_PROOFOFSTAKETIME_H
