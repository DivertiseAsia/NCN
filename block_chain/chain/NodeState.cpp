//
// Created by default on 3/4/2561.
//

#include "NodeState.h"

NodeState::NodeState(const Serializer* s, int si, const char* e, const Reward* r): serializer(s), encoding(e), size(si), chain(new Chain(r)) {
}

Block* NodeState::create_block() const {
    return new Block(transactions, chain->top_fingerprint().second->fingerprint);
}

Block* NodeState::add(std::string transaction, std::string public_key){
    transactions.emplace_back(std::pair<std::string, std::string>(transaction, public_key));
    if(transactions.size() == size) {
        return create_block();
    }
    return nullptr;
}
void NodeState::add(Block* block, std::string creator, int crypto){
    for(auto& a : block->transactions){
        auto i = find(transactions.begin(), transactions.end(), a);
        if(i != transactions.end())
            transactions.erase(i);
    }
    std::string dir(block->parent_fingerprint);
    std::string id(block->fingerprint);
    Chain* c = nullptr;
    if((c = chain->add(block, creator)) != nullptr)
        c->update_database(block, serializer, encoding.c_str(), crypto);
    std::string line;
    #if defined _WIN32
    _mkdir(std::string("./network/blocks/"+dir).c_str());
     #else
    mkdir(std::string("./network/blocks/"+dir).c_str(), 0700);
     #endif
    //mkdir(std::string("./network/blocks/"+dir).c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    std::ofstream block_file ("./network/blocks/"+dir+"/"+id+".blk");
    if(block_file.is_open()){
        block_file << serializer->serialize(block, encoding.c_str());
        block_file.close();
    }
}

void NodeState::read_blocks(int crypto) {
    #ifndef _WIN32
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
                    std::string creator = block->data->get_creator();
                    block_file.close();
                    Chain* c = nullptr;
                    if((c = chain->add(block, creator)) != nullptr)
                        c->update_database(block, serializer, encoding.c_str(), crypto);
                }
            }
        }
        closedir(dir);
        if(!list.empty())
            d = (*(list.end() - 1));
    }
    #else
    WIN32_FIND_DATA ffd;
    //LARGE_INTEGER filesize;
    TCHAR szDir[MAX_PATH];
    //size_t length_of_arg;
    HANDLE hFind = INVALID_HANDLE_VALUE;
    //DWORD dwError=0;

    std::vector<std::string> list;
    list.emplace_back("0");
    std::string d((*(list.end()-1)));
    while (!list.empty()) {
        StringCchCopy(szDir, MAX_PATH, std::string("./cmake-build-debug/network/blocks/"+d).c_str());
        StringCchCat(szDir, MAX_PATH, TEXT("\\*"));
        list.pop_back();
        hFind = FindFirstFile(szDir, &ffd);
        if(hFind != INVALID_HANDLE_VALUE ){
            do
            {
                std::string name = ffd.cFileName;
                std::ifstream block_file(std::string("./cmake-build-debug/network/blocks/" + d) + name);
                std::string folder(name);
                folder = folder.substr(0, folder.find('.'));
                if(folder.size() > 2){
                    list.emplace_back(folder);
                    std::string line;
                    while (block_file.is_open()) {
                        std::string serialized;
                        while (std::getline(block_file, line))
                            serialized += line;
                        Block *block = serializer->unserializeBlock(serialized, encoding.c_str());
                        std::string creator = block->data->get_creator();
                        block_file.close();
                        Chain* c = nullptr;
                        if((c = chain->add(block, creator)) != nullptr)
                            c->update_database(block, serializer, encoding.c_str());
                    }
                }
            }
            while (FindNextFile(hFind, &ffd) != 0);
        }
        FindClose(hFind);
        if(!list.empty())
            d = (*(list.end() - 1));
    }

    #endif
}

bool NodeState::check_transaction(Transaction* transaction, std::string k) {
    return chain->top_fingerprint().second->check_transaction(transaction, k);
}

void NodeState::show_current_state() {
    chain->top_fingerprint().second->show();
}

Block* NodeState::get(std::string& hash) {
    return chain->find(hash);
}

std::string NodeState::get_creator(std::string& hash) {
    return chain->find_creator(hash);
}

