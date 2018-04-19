//
// Created by default on 17/4/2561.
//

#include "Chain.h"
#include "../utils/RSA.h"

Chain::Chain(Block* b, Chain* c): database(c->database){
    block = b;
    fingerprint = b->fingerprint;
    b->data->update_database(&database);
}

Chain::Chain(Reward* r): fingerprint(nullptr), database(r){
}

Chain::~Chain(){
    chain.clear();
}

void Chain::add(Block* b){
    if(b->parent_fingerprint == nullptr || b->parent_fingerprint->hash == "0" || (fingerprint != nullptr && b->parent_fingerprint->hash == fingerprint->hash)){
        for(auto& a : chain)
            if(a->fingerprint->hash == b->fingerprint->hash)
                return;
        chain.emplace_back(new Chain(b, this));
    }
    else{
        for(auto& a : chain)
            a->add(b);
    }
}

std::pair<int, Chain*> Chain::top_fingerprint(){
    if(chain.empty())
        return std::pair<int, Chain*>(1, this);
    else{
        int size = 0;
        Chain* h(nullptr);
        for(auto& a : chain){
            std::pair<int, Chain*> tmp = a->top_fingerprint();
            if(tmp.first > size){
                size = tmp.first;
                h = tmp.second;
            }
        }
        return std::pair<int, Chain*>(size + 1, h);
    }
}

void Chain::update_database(Block* block, const Serializer* serializer, const char* encoding) {

    for(auto& pair : block->transactions){
        std::string key(Encoding::fromHexa(pair.second));
        RSA_Cryptography crypto(key);
        std::string t(Encoding::fromHexa(pair.first));
        Transaction* transaction = serializer->unserializeTransaction(crypto.decrypt(t, t.size()), encoding);
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
    }
}

bool Chain::check_transaction(Transaction* transaction, std::string k){
    std::string key(Encoding::toHexa(std::move(k)));
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

int Chain::count() const {
    int cpt = fingerprint != nullptr;
    for(auto& a : chain)
        cpt += a->count();
    return cpt;
}

void Chain::show() {
    for(auto a : database.rows){
        std::cout << a.first << "\n" << a.second->to_string() << std::endl;
    }
}

int Chain::find(Hash *pHash) {
    if(pHash == nullptr || pHash->hash == "0")
        return 1;
    else if(fingerprint != nullptr && fingerprint->hash == pHash->hash)
        return 1;
    else
        for(auto& a : chain)
            if(a->find(pHash))
                return 1;
    return 0;
}

Block* Chain::find(std::string str) {
    if(fingerprint != nullptr && fingerprint->hash == str)
        return block;
    else
        for(auto& a : chain) {
            Block* b = a->find(str);
            if(b != nullptr)
                return b;
        }
    return nullptr;
}
