//
// Created by default on 3/4/2561.
//

#include "Block.h"
#include <utility>
#include "../../utils/serialization/Serializer.h"
#include "../../kernel/messages/Message.h"
#include "../../algorithm/RSA.h"

std::string Block::compute_hash(int begin, int end, const Serializer* s, const char* e) const{
    if(begin == end) {
        std::string cipher(Encoding::fromHexa(transactions[begin].first));
        RSA_Cryptography crypto(Encoding::fromHexa(transactions[begin].second));
        return s->unserializeTransaction(crypto.decrypt(cipher, cipher.size()), e)->__hash__(s, e);
    }
    else
        return Hash::get_hash()->generate_hash(compute_hash(begin, begin + (end - begin) / 2, s, e), compute_hash(begin + (end - begin) / 2 + 1, end, s, e));
}
std::string Block::compute_fingerprint(const Serializer* s, const char* e) const {
    return Hash::get_hash()->generate_hash(compute_hash(0, transactions.size() - 1, s, e), timestamp);
}

Block::Block(std::vector<std::pair<std::string, std::string>> t, std::string parent): data(nullptr), transactions(
        std::move(
                std::move(t))), fingerprint(nullptr), parent_fingerprint(parent) {
    timestamp = std::chrono::duration_cast<std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch()).count();
}

void Block::update_fingerprint(const Serializer* s, const char* e){
    fingerprint = Hash::get_hash()->generate_hash(data->hash(), compute_fingerprint(s, e));
}
bool Block::checkFingerPrint(const Serializer* s, const char* e) const {
    std::string tmp = Hash::get_hash()->generate_hash(data->hash(), compute_fingerprint(s, e));
    bool b = fingerprint == tmp;
    return b;
}

Block::Block(): data(nullptr), fingerprint(nullptr) {

}

Block::~Block() {
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
    return e->put("fingerprint", ElementCreator::create(fingerprint))
            ->put("parent_fingerprint", ElementCreator::create(parent_fingerprint))
            ->put("timestamp", ElementCreator::create(timestamp))
            ->put("transactions", array)
            ->put("data", data->toElement()/*ElementCreator::create(serializer->serialize(data, encoding))*/);
}

void Block::fromElement(ElementObject* e, const Serializer* serializer, const char* encoding) {
    e->getItem("timestamp", &timestamp);
    ElementObject* o = nullptr;
    e->getItem("fingerprint", &fingerprint);
    e->getItem("parent_fingerprint", &parent_fingerprint);
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
