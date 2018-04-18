//
// Created by default on 12/4/2561.
//

#ifndef BLOCK_CHAIN_PROOFOFWORK_H
#define BLOCK_CHAIN_PROOFOFWORK_H


#include "Proof.h"

class ProofOfWork: public Proof {
public:
    void run(Block* block, Message*) override;
    bool accept(Block* block, Message*) override;
};


#endif //BLOCK_CHAIN_PROOFOFWORK_H
