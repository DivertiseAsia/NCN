//
// Created by default on 10/4/2561.
//

#include "TransactionContainer.h"
#include "../../../Serializer.h"

TransactionContainer::TransactionContainer(Transaction* tr, std::string t, std::string c, std::string p, Serializer* serializer, const char* encoding): transaction(tr), transac(t), cipher(c), public_key(p) {
    __hash__(serializer, encoding);
}

Element* TransactionContainer::toElement() const {

    ElementObject* e = ElementCreator::creator.object();
    ElementCreator::creator.put(e, "transaction", ElementCreator::creator.create(transac))
                          ->put(e, "public_key", ElementCreator::creator.create(public_key))
                          ->put(e, "cipher", ElementCreator::creator.create(cipher));
    return e;
}

void TransactionContainer::fromElement(ElementObject* e, const Serializer* serializer, const char* encoding) {
    e->getItem("public_key", &public_key);
    e->getItem("cipher", &cipher);
    e->getItem("transaction", &transac);
    transaction = serializer->unserializeTransaction(transac, encoding);
    __hash__(serializer, encoding);
}

std::string TransactionContainer::to_string() const {
    return std::string("");
}


TransactionContainer::TransactionContainer() = default;

void TransactionContainer::__hash__(const Serializer* serializer, const char* encoding) {
    hash = new Hash(transaction, serializer, encoding);
}

bool TransactionContainer::operator()() const {
    return true;
}