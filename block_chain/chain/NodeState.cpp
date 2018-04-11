//
// Created by default on 3/4/2561.
//

#include "NodeState.h"
#include "../utils/RSA.h"

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
    update_database(block);
    std::cout << "read files" << std::endl;
    std::ofstream block_file ("network/blocks/"+id+".blk");
    std::string line;
    if(block_file.is_open()){
        block_file << serializer->serialize(block, "json");
        block_file.close();
    }
}

void NodeState::update_database(Block* block){
    for(auto& pair : block->transactions){
        std::string key(Encoding::fromHexa(pair.second));
        RSA_Cryptography crypto(key);
        std::string t(Encoding::fromHexa(pair.first));
        Transaction* transaction = serializer->unserializeTransaction(crypto.decrypt(t, t.size()), "json");
        auto it = database.rows.find(pair.second);
        Row* row;
        if(it == database.rows.end()) {
            row = transaction->createRow();
            database.rows[pair.second] = row;
        }
        else
            row = it->second;
        std::vector<std::string> targets = transaction->apply(row);
        for(auto& target : targets){
            auto iterator = database.rows.find(target);
            Row* updated_row;
            if(it == database.rows.end()){
                updated_row = transaction->createRow();
                database.rows[target] = updated_row;
            }
            else
                updated_row = iterator->second;
            transaction->apply_reverse(updated_row);
        }
        std::cout << std::endl;
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
        update_database(block);
        block_file.close();
        id = block->fingerprint->to_string();
        block_file.open("blocks/"+id+".blk");
        top_fingerprint = block->fingerprint;
    }
}

bool NodeState::check_transaction(Transaction* transaction, std::string k) {
    std::string key(Encoding::toHexa(k));
    auto it = database.rows.find(key);
    Row* row;
    if(it == database.rows.end()) {
        row = transaction->createRow();
        database.rows[key] = row;
    }
    else
        row = it->second;
    return transaction->validate(row);
}
