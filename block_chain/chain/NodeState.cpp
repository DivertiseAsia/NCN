//
// Created by default on 3/4/2561.
//

#include "NodeState.h"

NodeState::NodeState(Serializer* s, int si, const char* e, Reward* r): serializer(s), size(si), chain(new Chain(r)), encoding(e) {
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
    for(auto& a : block->transactions){
        auto i = find(transactions.begin(), transactions.end(), a);
        if(i != transactions.end())
            transactions.erase(i);
    }
    std::string dir(block->parent_fingerprint->hash);
    std::string id(block->fingerprint->hash);
    Chain* c = nullptr;
    if((c = chain->add(block)) != nullptr)
        c->update_database(block, serializer, encoding.c_str());
    std::string line;
    mkdir(std::string("./network/blocks/"+dir).c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    std::ofstream block_file ("./network/blocks/"+dir+"/"+id+".blk");
    if(block_file.is_open()){
        block_file << serializer->serialize(block, encoding.c_str());
        block_file.close();
    }
}

void NodeState::update_database(Block* block){
    chain->top_fingerprint().second->update_database(block, serializer, encoding.c_str());
}

void NodeState::read_blocks() {
    std::vector<std::string> list;
    list.emplace_back("0");
    DIR *dir;
    struct dirent *ent;
    std::string d((*(list.end()-1)));
    while (!list.empty()) {
        dir = opendir(std::string("./network/blocks/" + d).c_str());
        list.pop_back();
        while (dir && (ent = readdir(dir)) != nullptr) {
            if(ent->d_name[0] != '.') {
                std::ifstream block_file(std::string("./network/blocks/" + d + "/") + ent->d_name);
                std::string folder(ent->d_name);
                folder = folder.substr(0, folder.find('.'));
                list.emplace_back(folder);
                std::string line;
                while (block_file.is_open()) {
                    std::string serialized;
                    while (std::getline(block_file, line))
                        serialized += line;
                    Block *block = serializer->unserializeBlock(serialized, encoding.c_str());
                    block_file.close();
                    Chain* c = nullptr;
                    if((c = chain->add(block)) != nullptr)
                        c->update_database(block, serializer, encoding.c_str());
                }
            }
        }
        closedir(dir);
        if(!list.empty())
            d = (*(list.end() - 1));
    }
}

bool NodeState::check_transaction(Transaction* transaction, std::string k) {
    return chain->top_fingerprint().second->check_transaction(transaction, k);
}

void NodeState::show_current_state() {
    chain->top_fingerprint().second->show();
}

bool NodeState::get(Hash *pHash) {
    return chain->find(pHash) != 0;
}

Block* NodeState::get(std::string& hash) {
    return chain->find(hash);
}

