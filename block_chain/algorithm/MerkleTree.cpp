//
// Created by default on 11/4/2561.
//

#include "MerkleTree.h"
#include "../utils/serialization/Serializer.h"
#include "cryptography/RSA.h"

MerkleTree::MerkleTree(Transaction* transaction, const Serializer* serializer, const char* encoding): left(nullptr), right(nullptr), value(transaction->__hash__(serializer, encoding)){

}
MerkleTree::MerkleTree(MerkleTree* l, MerkleTree* r): left(l), right(r), value(Hash::get_hash()->generate_hash(left->value, right->value)) {

}
MerkleTree::MerkleTree(Block* block, const Serializer* serializer, const char* encoding, int c): left(nullptr), right(nullptr), value("")
{
    std::vector<Transaction*> transactions;
    for(auto& p : block->transactions){
        Cryptography* crypto(Cryptography::generate(c, Encoding::fromHexa(p.first)));
        std::string t(crypto->decrypt(p.second, p.second.size()));
        transactions.emplace_back(serializer->unserializeTransaction(t, encoding));
        delete crypto;
    }
    generate_tree(transactions, 0, (int)transactions.size() - 1, serializer, encoding);
}

MerkleTree::MerkleTree(std::vector<Transaction*> transactions, const Serializer* serializer, const char* encoding): left(nullptr), right(nullptr), value("")
{
    generate_tree(transactions, 0, (int)transactions.size() - 1, serializer, encoding);
}

void MerkleTree::generate_tree(std::vector<Transaction*> transactions, int begin, int end, const Serializer* s, const char* e) {
    if(begin == end)
        value = (transactions[begin]->__hash__(s, e));
    else {
        std::size_t const half_size = transactions.size() / 2;
        std::vector<Transaction*> split_lo(transactions.begin(), transactions.begin() + half_size);
        std::vector<Transaction*> split_hi(transactions.begin() + half_size, transactions.end());
        left = new MerkleTree(split_lo, s, e);
        right = new MerkleTree(split_hi, s, e);
    }
}
MerkleTree::MerkleTree(): left(nullptr), right(nullptr), value(""){

}
MerkleTree::~MerkleTree(){
    delete left;
    delete right;
}

Element* MerkleTree::toElement() const{
    ElementObject* e = ElementCreator::object();
    return e->put("value", ElementCreator::create(value))
            ->put("left", left ? left->toElement() : ElementCreator::object())
            ->put("right", right ? right->toElement() : ElementCreator::object());
}

void MerkleTree::fromElement(ElementObject* e, const Serializer* serializer, const char* encoding) {
    ElementObject *o = nullptr;
    e->getItem("value", &value);

    e->getItem("left", &o);
    if(o && !o->values.empty()) {
        left = new MerkleTree();
        left->fromElement(o, serializer, encoding);
    }
    else
        left = nullptr;

    e->getItem("right", &o);
    if(o && !o->values.empty()) {
        right = new MerkleTree();
        right->fromElement(o, serializer, encoding);
    }
    else
        right = nullptr;
}

int MerkleTree::size() const{
    int i = 0;
    if(left)
        i += left->size();
    if(right)
        i += right->size();
    if(!left && !right)
        return 1;
    return i;
}

std::string MerkleTree::get_hash(const int i) const {
    if(left == nullptr && right == nullptr)
        return value;
    else if(i < size()/2)
        return left->get_hash(i);
    else
        return right->get_hash(i - size()/2);
}
