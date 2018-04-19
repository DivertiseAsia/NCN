//
// Created by default on 19/4/2561.
//

#include "BlockMessage.h"

BlockMessage::BlockMessage(std::string b, std::string k, MerkleTree* tr): Message(Message::BLOCK), block(std::move(b)), key(Encoding::toHexa(std::move(k))), tree(tr)
{
}

BlockMessage::BlockMessage() = default;

BlockMessage::~BlockMessage() = default;

Element* BlockMessage::toElement() const {
    ElementObject* e = ElementCreator::object();
    return e->put("block", ElementCreator::create(block))
            ->put("key", ElementCreator::create(key))
            ->put("type", ElementCreator::create(type))
            ->put("tree", tree != nullptr ? tree->toElement() : ElementCreator::create(type));;
}

void BlockMessage::fromElement(ElementObject* e, const Serializer* serializer, const char* encoding) {
    e->getItem("block", &block);
    e->getItem("key", &key);
    e->getItem("type", &type);
    ElementObject* o = nullptr;
    e->getItem("tree", &o);
    if(o && !o->values.empty()) {
        tree = new MerkleTree();
        tree->fromElement(o, serializer, encoding);
    }
    else
        tree = nullptr;
}

const std::string BlockMessage::get_key() const {
    return key;
}
