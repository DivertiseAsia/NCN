//
// Created by default on 12/4/2561.
//

#include "ProofOfWork.h"
#include "metadata/ProofOfWorkMetadata.h"
#include "../../../kernel/messages/BlockMessage.h"

void ProofOfWork::run(Block* block, std::string key)const {
    std::string tmp = Hash::get_hash()->generate_hash((!block->parent_fingerprint.empty() ? block->parent_fingerprint : "0") + key);
    for(long long int i = 1; i > 0 ; i++){
        std::string t = Hash::get_hash()->generate_hash(tmp, i);
        for(long long int j = 1; j > 0 ; j++) {
            std::string h = Hash::get_hash()->generate_hash(t, j);
            if(h.substr(0, 1) == "0"){
                block->data = new ProofOfWorkMetadata(i, j, key);
                return;
            }
        }
    }
}

bool ProofOfWork::accept(Block* block, Message*)const {
    auto data = dynamic_cast<ProofOfWorkMetadata*>(block->data);
    std::string tmp = Hash::get_hash()->generate_hash((!block->parent_fingerprint.empty() ? block->parent_fingerprint : "0") + data->get_creator());
    std::string t = Hash::get_hash()->generate_hash(tmp, data->first);
    std::string h = Hash::get_hash()->generate_hash(t, data->second);
    return h.substr(0, 1) == "0";
}