//
// Created by default on 4/4/2561.
//

#include "Serializer.h"

ElementObject* Serializer::getElement(std::string transaction, const char* key) const{
    Element* element = new ElementObject();
    parsers.get(key)->parse(transaction, &element);
    ElementObject* e = dynamic_cast<ElementObject*>(element);
    return e;
}
char* Serializer::serialize(Component* component, const char* key) const{
    Element* element = component->toElement();
    return serialize(element, key);
}

char* Serializer::serialize(Element* element, const char* key) const{
    std::string parsed;
    creators.get(key)->parse(parsed, &element);
    char* v = (char*)malloc((int)parsed.size());
    strcpy(v, parsed.c_str());
    return v;
}

Transaction* Serializer::unserializeTransaction(std::string transaction, const char* key) const {
    Element* element = new Element();
    creators.get(key)->parse(transaction, &element);
    return nullptr;//TODO: new Transaction(element);
}
Message* Serializer::unserializeMessage(std::string message, const char* key) const {
    Message* m = new Message();
    m->__init__(getElement(message, key));
    return m;
}
Block* Serializer::unserializeBlock(std::string block, const char* key) const {
    Block* b = new Block(this, key);
    b->__init__(getElement(block, key));
    return b;
}

void Serializer::set_serializer(const char* key, ContentCreator* creator) {
    creators.put(key, creator);
}

void Serializer::set_unserializer(const char* key, ContentParser* parser) {
    parsers.put(key, parser);
}
