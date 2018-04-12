//
// Created by default on 11/4/2561.
//

#include "MerkleTree.h"

MerkleTree::MerkleTree(Transaction* transaction, const Serializer* serializer, const char* encoding): value(transaction->__hash__(serializer, encoding)), left(nullptr), right(nullptr){

}
MerkleTree::MerkleTree(MerkleTree* l, MerkleTree* r): left(l), right(r), value(new Hash(left->value, right->value)) {

}
MerkleTree::MerkleTree(std::vector<Transaction*> transactions, const Serializer* serializer, const char* encoding): value(nullptr), left(nullptr), right(nullptr)
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
MerkleTree::MerkleTree(): value(nullptr), left(nullptr), right(nullptr){

}
MerkleTree::~MerkleTree(){
    delete value;
    delete left;
    delete right;
}

Element* MerkleTree::toElement() const{
    ElementObject* e = ElementCreator::object();
    e->put("value", value ? value->toElement() : ElementCreator::object())
            ->put("left", left ? left->toElement() : ElementCreator::object())
            ->put("right", right ? right->toElement() : ElementCreator::object());
    return e;
}

void MerkleTree::fromElement(ElementObject* e, const Serializer* serializer, const char* encoding) {
    ElementObject *o = nullptr;
    value = new Hash();
    e->getItem("value", &o);
    value->fromElement(o, serializer, encoding);

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
Hash* MerkleTree::get_hash(const int i) const {
    if(left == nullptr && right == nullptr)
        return value;
    else if(i < size()/2)
        return left->get_hash(i);
    else
        return right->get_hash(i - size()/2);
}
