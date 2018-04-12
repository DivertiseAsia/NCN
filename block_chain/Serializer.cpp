//
// Created by default on 4/4/2561.
//

#include "Serializer.h"
#include <utility>

ElementObject* Serializer::getElement(std::string transaction, const char* key) const{
    Element* element = new ElementObject();
    parsers.get(key)->parse(transaction, &element);
    auto * e = dynamic_cast<ElementObject*>(element);
    return e;
}
char* Serializer::serialize(const Component* component, const char* key) const{
    Element* element = component->toElement();
    return serialize(element, key);
}

char* Serializer::serialize(Element* element, const char* key) const{
    std::string parsed;
    creators.get(key)->parse(parsed, &element);
    auto * v = (char*)malloc((int)parsed.size() + 1);
    strcpy(v, parsed.c_str());
    v[parsed.size()] = 0;
    return v;
}

TransactionContainer* Serializer::unserializeTransactionContainer(std::string message, const char* key) const {
    auto * m = new TransactionContainer();
    ElementObject* e = getElement(std::move(message), key);
    m->__init__(e, this, key);
    return m;
}

Transaction* Serializer::unserializeTransaction(std::string transaction, const char* key) const {
    auto * element = new Element();
    creators.get(key)->parse(transaction, &element);
    return nullptr;
}
Message* Serializer::unserializeMessage(std::string message, const char* key) const {
    auto * m = new Message();
    m->__init__(getElement(std::move(message), key), this, key);
    return m;
}
Block* Serializer::unserializeBlock(std::string block, const char* key) const {
    auto * b = new Block(this, key);
    b->__init__(getElement(std::move(block), key), this, key);
    return b;
}

void Serializer::set_serializer(const char* key, ContentCreator* creator) {
    creators.put(key, creator);
}

void Serializer::set_unserializer(const char* key, ContentParser* parser) {
    parsers.put(key, parser);
}
