//
// Created by default on 3/4/2561.
//

#include "Block.h"
#include "../../Serializer.h"

Hash* Block::compute_hash(int begin, int end) const{
    if(begin == end)
        return transactions[begin]->hash;
    else
        return new Hash(compute_hash(begin, begin + (end - begin) / 2), compute_hash(begin + (end - begin) / 2 + 1, end));
}
Hash* Block::compute_fingerprint() const {
    return compute_hash(0, transactions.size() - 1);
}

Block::Block(std::vector<Transaction*> t, Hash* parent): transactions(t), parent_fingerprint(parent) {
    fingerprint = compute_fingerprint();
}

bool Block::checkFingerPrint() const {
    return *fingerprint == *compute_fingerprint();
}

Block::Block(const Serializer* s, const char* e): serializer(s), encoding(e) {

}

Block::~Block(){
}

Element* Block::toElement() {
    ElementArray* array = ElementCreator::creator.array();
    for(std::vector<Transaction*>::iterator it = transactions.begin(); it != transactions.end(); it++)
        array->add((*it)->toElement());
    ElementObject* e = ElementCreator::creator.object();
    ElementCreator::creator.put(e, "fingerprint", fingerprint ? fingerprint->toElement() : ElementCreator::creator.object())
                          ->put(e, "parent_fingerprint", parent_fingerprint ? parent_fingerprint->toElement() : ElementCreator::creator.object())
                          ->put(e, "transactions", array)
                          ->put(e, "data", data.toElement());
    return e;
}

void Block::fromElement(ElementObject* e) {
    ElementObject* o = ElementCreator::creator.object();
    fingerprint = new Hash();
    fingerprint->fromElement(o);
    e->getItem("parent_fingerprint", o);
    parent_fingerprint = new Hash();
    parent_fingerprint->fromElement(o);
    e->getItem("data", o);
    data.fromElement(o);
    ElementArray* a = ElementCreator::creator.array();
    e->getItem("transactions", a);
    for(std::vector<Element*>::iterator it = a->values.begin(); it != a->values.end(); it++)
        transactions.push_back(serializer->unserializeTransaction(serializer->serialize(*it, encoding), encoding));
    //delete o;
    //delete a;
}

