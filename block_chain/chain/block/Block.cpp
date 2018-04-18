//
// Created by default on 3/4/2561.
//

#include "Block.h"
#include <utility>
#include "../../Serializer.h"
#include "../../Message.h"
#include "../../utils/RSA.h"
#include "../../proof/metadatas/ProofOfWorkMetadata.h"

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
    return new Hash(compute_hash(0, transactions.size() - 1, s, e), timestamp);
}

Block::Block(std::vector<std::pair<std::string, std::string>> t, Hash* parent, const Serializer* s, const char* e): serializer(s), encoding(e), transactions(
        std::move(
                std::move(t))), parent_fingerprint(parent), data(nullptr), fingerprint(nullptr) {
    timestamp = std::chrono::duration_cast<std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch()).count();
}

void Block::update_fingerprint(){
    fingerprint = new Hash(data->hash(), compute_fingerprint(serializer, encoding));
}
bool Block::checkFingerPrint(const Serializer* s, const char* e) const {
    Hash* tmp = new Hash(data->hash(), compute_fingerprint(serializer, encoding));
    bool b = *fingerprint == *tmp;
    delete tmp;
    return b;
}

Block::Block(const Serializer* s, const char* e): serializer(s), encoding(e), fingerprint(nullptr), data(nullptr) {

}

Block::~Block() {
    delete fingerprint;
    delete data;
};

Element* Block::toElement() const{
    ElementArray* array = ElementCreator::array();
    for (auto &transaction : transactions) {
        ElementObject* object = ElementCreator::object();
        object->put("first", ElementCreator::create(transaction.first));
        object->put("second", ElementCreator::create(transaction.second));
        array->add(object);
    }
    ElementObject* e = ElementCreator::object();
    return e->put("fingerprint", fingerprint ? fingerprint->toElement() : ElementCreator::object())
            ->put("parent_fingerprint", parent_fingerprint ? parent_fingerprint->toElement() : ElementCreator::object())
            ->put("timestamp", ElementCreator::create(timestamp))
            ->put("transactions", array)
            ->put("data", data->toElement()/*ElementCreator::create(serializer->serialize(data, encoding))*/);
}

void Block::fromElement(ElementObject* e, const Serializer* serializer, const char* encoding) {
    e->getItem("timestamp", &timestamp);
    ElementObject* o = nullptr;
    fingerprint = new Hash();
    e->getItem("fingerprint", &o);
    fingerprint->fromElement(o, serializer, encoding);
    parent_fingerprint = new Hash();
    e->getItem("parent_fingerprint", &o);
    parent_fingerprint->fromElement(o, serializer, encoding);
    e->getItem("data", &o);
    data = serializer->unserializeMetadata(serializer->serialize(o, encoding), encoding);
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
