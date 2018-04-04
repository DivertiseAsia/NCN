//
// Created by default on 3/4/2561.
//

#include "Chain.h"

Chain::Chain(int s): size(s) {

}

Block* Chain::create_block() const {
    return new Block(transactions);
}

Block* Chain::add(Transaction* transaction){
    transactions.push_back(transaction);
    if(transactions.size() == size) {
        return create_block();
    }
    return nullptr;
}
void Chain::add(Block const& block){
    std::cout << "read files" << std::endl;
    std::string id(block.parent_hash.to_string());
    std::ofstream block_file ("blocks/"+id+".blk");
    std::string line;
    if(block_file.is_open()){
        block_file << "TODO\n";
        block_file.close();
    }
}

void Chain::read_blocks() {
    std::string id("0000000000000000");
    std::ifstream block_file ("blocks/"+id+".blk");
    std::string line;
    while(block_file.is_open()){
        while (std::getline (block_file, line))
            std::cout << line << std::endl;
        block_file.close();
        id = "TODO";
        block_file.open("blocks/"+id+".blk");//block.hash
    }
    top.set_hash(id);
}