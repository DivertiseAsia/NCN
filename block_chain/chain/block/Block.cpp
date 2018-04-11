//
// Created by default on 3/4/2561.
//

#include "Block.h"
#include "../../Serializer.h"
#include "../../Message.h"
#include "../../utils/RSA.h"

Hash* Block::compute_hash(int begin, int end, const Serializer* s, const char* e) const{
    if(begin == end) {
        std::string cipher(Encoding::fromHexa(transactions[begin].first));
        RSA_Cryptography crypto(Encoding::fromHexa(transactions[begin].second));
        return s->unserializeTransaction(crypto.decrypt(cipher, cipher.size()), e)->__hash__(s, e);
    }
    else
        return new Hash(compute_hash(begin, begin + (end - begin) / 2, s, e), compute_hash(begin + (end - begin) / 2 + 1, end, s, e));
}
Hash* Block::compute_fingerprint(const Serializer* s, const char* e) const {
    return compute_hash(0, transactions.size() - 1, s, e);
}

Block::Block(std::vector<std::pair<std::string, std::string>> t, Hash* parent, const Serializer* s, const char* e): transactions(t), parent_fingerprint(parent) {
    fingerprint = compute_fingerprint(s, e);
}

bool Block::checkFingerPrint(const Serializer* s, const char* e) const {
    return *fingerprint == *compute_fingerprint(s, e);
}

Block::Block(const Serializer* s, const char* e): serializer(s), encoding(e) {

}

Block::~Block(){
}

Element* Block::toElement() const{
    ElementArray* array = ElementCreator::creator.array();
    for (auto &transaction : transactions) {
        ElementObject* object = ElementCreator::creator.object();
        object->put("first", ElementCreator::creator.create(transaction.first));
        object->put("second", ElementCreator::creator.create(transaction.second));
        array->add(object);
    }
    ElementObject* e = ElementCreator::creator.object();
    ElementCreator::creator.put(e, "fingerprint", fingerprint ? fingerprint->toElement() : ElementCreator::creator.object())
                          ->put(e, "parent_fingerprint", parent_fingerprint ? parent_fingerprint->toElement() : ElementCreator::creator.object())
                          ->put(e, "transactions", array)
                          ->put(e, "data", data.toElement());
    return e;
}

void Block::fromElement(ElementObject* e, const Serializer* serializer, const char* encoding) {
    ElementObject* o = nullptr;
    fingerprint = new Hash();
    e->getItem("fingerprint", &o);
    fingerprint->fromElement(o, serializer, encoding);
    parent_fingerprint = new Hash();
    e->getItem("parent_fingerprint", &o);
    parent_fingerprint->fromElement(o, serializer, encoding);
    e->getItem("data", &o);
    data.fromElement(o);
    ElementArray* a = nullptr;
    e->getItem("transactions", &a);
    for (auto &value : a->values) {
        auto elem = dynamic_cast<ElementObject*>(value);
        std::string first;
        std::string second;
        elem->getItem("first", &first);
        elem->getItem("second", &second);
        transactions.emplace_back(std::pair<std::string, std::string>(first, second));
    }
}

std::string Block::to_string() const {
    std::string res = "BLOCK";
    return res;
}