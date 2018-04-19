//
// Created by default on 4/4/2561.
//

#include "Serializer.h"
#include "json/JsonCreator.hpp"
#include "json/JsonParser.hpp"
#include "../../proof/metadatas/ProofOfWorkMetadata.h"
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

Transaction* Serializer::unserializeTransaction(std::string transaction, const char* key) const {
    auto * element = new Element();
    creators.get(key)->parse(transaction, &element);
    return nullptr;
}
Message* Serializer::unserializeMessage(std::string message, const char* key) const {
    ElementObject* o = getElement(std::move(message), key);
    int type;
    o->getItem("type", &type);
    Message* m = Message::generate(type);
    m->__init__(o, this, key);
    return m;
}
Block* Serializer::unserializeBlock(std::string block, const char* key) const {
    auto * b = new Block(this, key);
    b->__init__(getElement(std::move(block), key), this, key);
    return b;
}
Metadata* Serializer::unserializeMetadata(std::string data, const char* key) const{
    static std::map<int, std::function<Metadata*()>> datas;
    if(datas.empty()) {
        datas[0] = []() -> Metadata*{return new ProofOfWorkMetadata;};
    }
    ElementObject* o = getElement(std::move(data), key);
    int type;
    o->getItem("type", &type);
    Metadata* m = datas.find(type)->second();
    m->__init__(o, this, key);
    return m;
}

void Serializer::set_serializer(const char* key, ContentCreator* creator) {
    creators.put(key, creator);
}

void Serializer::set_unserializer(const char* key, ContentParser* parser) {
    parsers.put(key, parser);
}

Serializer::Serializer() {
    set_serializer("json", new JsonCreator());
    set_unserializer("json", new JsonParser());
}
