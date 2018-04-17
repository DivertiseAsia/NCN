//
// Created by default on 3/4/2561.
//

#include "NodeState.h"
#include <utility>
#include "../utils/RSA.h"

NodeState::NodeState(Serializer* s, int si, const char* e): serializer(s), size(si), chain(new Chain()), encoding(e) {
}

Block* NodeState::create_block() const {
    return new Block(transactions, chain->top_fingerprint().second->fingerprint, serializer, encoding.c_str());
}

Block* NodeState::add(std::string transaction, std::string public_key){
    transactions.emplace_back(std::pair<std::string, std::string>(transaction, public_key));
    if(transactions.size() == size) {
        return create_block();
    }
    return nullptr;
}
void NodeState::add(Block* block){
    block->parent_fingerprint = chain->top_fingerprint().second->fingerprint;
    std::string id(block->parent_fingerprint != nullptr ? block->parent_fingerprint->to_string() : "0");
    chain->add(block);
    update_database(block);
    std::ofstream block_file ("./network/blocks/"+id+".blk");
    std::string line;
    if(block_file.is_open()){
        block_file << serializer->serialize(block, encoding.c_str());
        block_file.close();
    }
}

void NodeState::update_database(Block* block){
    chain->top_fingerprint().second->update_database(block, serializer, encoding.c_str());
}

void NodeState::clear_transactions() {
    transactions.clear();
}

void NodeState::read_blocks() {
    std::string id("0");
    std::ifstream block_file("./network/blocks/"+id+".blk");
    std::string line;
    while(block_file.is_open()){
        std::string serialized;
        while (std::getline (block_file, line))
            serialized += line;
        Block* block = serializer->unserializeBlock(serialized, encoding.c_str());
        update_database(block);
        block_file.close();
        id = block->fingerprint->hash;
        block_file.open("./network/blocks/"+id+".blk");
        chain->add(block);
    }
}

bool NodeState::check_transaction(Transaction* transaction, std::string k) {
    return chain->top_fingerprint().second->check_transaction(transaction, k);
}
