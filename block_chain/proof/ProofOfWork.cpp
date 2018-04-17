//
// Created by default on 12/4/2561.
//

#include "ProofOfWork.h"
#include "metadatas/ProofOfWorkMetadata.h"

void ProofOfWork::run(Block* block){
    for(double i = 1; i > 0 ; i++){
        for(double j = 1; j > 0 ; j++) {
            Hash tmp(block->fingerprint, i);
            Hash h(&tmp, j);
            if(h.hash.substr(0, 3) == "000"){
                block->data = new ProofOfWorkMetadata(i, j);
                return;
            }
        }
    }
}

bool ProofOfWork::accept(Block* block){
    auto data = dynamic_cast<ProofOfWorkMetadata*>(block->data);
    Hash tmp(block->fingerprint, data->first);
    Hash h(&tmp, data->second);
    return h.hash.substr(0, 3) == "000";
}