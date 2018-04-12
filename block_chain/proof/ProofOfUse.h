//
// Created by default on 12/4/2561.
//

#ifndef BLOCK_CHAIN_PROOFOFUSE_H
#define BLOCK_CHAIN_PROOFOFUSE_H


#include "Proof.h"

class ProofOfUse: public Proof {
public:
    void run(Block* block) override;
    bool accept(Block* block) override;
};


#endif //BLOCK_CHAIN_PROOFOFUSE_H
