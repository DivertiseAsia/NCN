//
// Created by default on 3/4/2561.
//

#include "NodeState.h"

NodeState::NodeState(Serializer* s, int si): serializer(s), size(si), top_fingerprint(nullptr) {
}

Block* NodeState::create_block() const {
    return new Block(transactions, top_fingerprint, serializer, "json");
}

Block* NodeState::add(std::string transaction, std::string public_key){
    transactions.emplace_back(std::pair<std::string, std::string>(transaction, public_key));
    if(transactions.size() == size) {
        return create_block();
    }
    return nullptr;
}
void NodeState::add(Block* block){
    block->parent_fingerprint = top_fingerprint;
    std::string id(top_fingerprint != nullptr ? top_fingerprint->to_string() : "0");
    top_fingerprint = block->fingerprint;
    //TODO : apply each transaction to the memory
    std::cout << "read files" << std::endl;
    std::ofstream block_file ("network/blocks/"+id+".blk");
    std::string line;
    if(block_file.is_open()){
        block_file << serializer->serialize(block, "json");
        block_file.close();
    }
}

void NodeState::clear_transactions() {
    transactions.clear();
}

void NodeState::read_blocks() {
    std::string id("0");
    std::ifstream block_file("network/blocks/"+id+".blk");
    std::string line;
    while(block_file.is_open()){
        std::string serialized;
        while (std::getline (block_file, line))
            serialized += line;
        Block* block = serializer->unserializeBlock(serialized, "json");
        block_file.close();
        id = block->fingerprint->to_string();
        block_file.open("blocks/"+id+".blk");
        top_fingerprint = block->fingerprint;
    }
}