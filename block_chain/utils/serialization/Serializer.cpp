//
// Created by default on 4/4/2561.
//

#include "Serializer.h"

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
    ElementObject* o = getElement(std::move(transaction), key);
    int type;
    o->getItem("type", &type);
    Transaction* t = transactions_index.find(type)->second();
    t->__init__(o, this, key);
    return t;
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
    auto * b = new Block();
    b->__init__(getElement(std::move(block), key), this, key);
    return b;
}
Metadata* Serializer::unserializeMetadata(std::string data, const char* key) const{
    ElementObject* o = getElement(std::move(data), key);
    int type;
    o->getItem("type", &type);
    Metadata* m = metadata_index.find(type)->second();
    m->__init__(o, this, key);
    return m;
}

void Serializer::add_serializer(ContentCreator* creator) {
    creators.put(creator->get_encoding(), creator);
}

void Serializer::add_unserializer(ContentParser* parser) {
    parsers.put(parser->get_encoding(), parser);
}

Serializer::Serializer() {
    add_serializer(new JsonCreator());
    add_unserializer(new JsonParser());
    add_metadata(ProofOfWorkMetadata::TYPE, []() -> Metadata*{return new ProofOfWorkMetadata;});
}

Serializer::~Serializer(){
    creators.clear();
    parsers.clear();
}


void Serializer::add_metadata(int id, std::function<Metadata*()> metadata){
    metadata_index[id] = std::move(metadata);
}

void Serializer::add_transaction(int id, std::function<Transaction*()> transaction){
    transactions_index[id] = std::move(transaction);

}
