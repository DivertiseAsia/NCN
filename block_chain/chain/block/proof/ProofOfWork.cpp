//
// Created by default on 12/4/2561.
//

#include "ProofOfWork.h"
#include "metadatas/ProofOfWorkMetadata.h"
#include "../../../kernel/messages/BlockMessage.h"

void ProofOfWork::run(Block* block, std::string key){
    Hash tmp((block->parent_fingerprint != nullptr ? block->parent_fingerprint->to_string() : "0") + key);
    for(long long int i = 1; i > 0 ; i++){
        Hash t(&tmp, i);
        for(long long int j = 1; j > 0 ; j++) {
            Hash h(&t, j);
            if(h.to_string().substr(0, 1) == "0"){
                block->data = new ProofOfWorkMetadata(i, j, key);
                return;
            }
        }
    }
}

bool ProofOfWork::accept(Block* block, Message* m){
    auto data = dynamic_cast<ProofOfWorkMetadata*>(block->data);
    Hash tmp((block->parent_fingerprint != nullptr ? block->parent_fingerprint->to_string() : "0") + data->winner);
    Hash t(&tmp, data->first);
    Hash h(&t, data->second);
    return h.to_string().substr(0, 1) == "0";
}