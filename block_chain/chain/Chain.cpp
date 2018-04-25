//
// Created by default on 17/4/2561.
//

#include "Chain.h"
#include "../algorithm/cryptography/RSA.h"

Chain::Chain(Block* b, Chain* c, std::string cr): database(c->database), fingerprint(b->fingerprint), block(b), creator(std::move(cr)) {
    b->data->update_database(&database);
}

Chain::Chain(const Reward* r): database(r), fingerprint(nullptr){
}

Chain::~Chain(){
    chain.clear();
}

Chain* Chain::add(Block* b, std::string creator){
    if(b->parent_fingerprint == "" || b->parent_fingerprint == "0" || (b->parent_fingerprint == fingerprint)){
        for(auto& a : chain)
            if(a->fingerprint == b->fingerprint)
                return nullptr;
        Chain* c = new Chain(b, this, creator);
        chain.emplace_back(c);
        return c;
    }
    else{
        Chain* c = nullptr;
        for(auto& a : chain){
            c = a->add(b, creator);
            if(c)
                return c;
        }
    }
    return nullptr;
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

void Chain::update_database(Block* block, const Serializer* serializer, const char* encoding, int c) {

    for(auto& pair : block->transactions){
        std::string key(Encoding::fromHexa(pair.second));
        Cryptography* crypto(Cryptography::generate(c, key));
        std::string t(Encoding::fromHexa(pair.first));
        Transaction* transaction = serializer->unserializeTransaction(crypto->decrypt(t, t.size()), encoding);
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
        delete crypto;
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
    int cpt = !(fingerprint == "0" || fingerprint.empty());
    for(auto& a : chain)
        cpt += a->count();
    return cpt;
}

void Chain::show() {
    for(auto a : database.rows){
        std::cout << a.first << "\n" << a.second->to_string() << std::endl;
    }
}

Block* Chain::find(std::string str) {
    if(fingerprint == str)
        return block;
    else
        for(auto& a : chain) {
            Block* b = a->find(str);
            if(b != nullptr)
                return b;
        }
    return nullptr;
}

std::string Chain::find_creator(std::string& hash) {
    if(fingerprint == hash)
        return creator;
    else
        for(auto& a : chain) {
            Block* b = a->find(hash);
            if(b != nullptr)
                return creator;
        }
    return nullptr;
}
