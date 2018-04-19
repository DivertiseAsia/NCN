//
// Created by default on 19/4/2561.
//

#include "BlockAnswerMessage.h"

BlockAnswerMessage::BlockAnswerMessage(std::string p): Message(Message::ANSWER_BLOCK), block(std::move(p)) {
}

BlockAnswerMessage::BlockAnswerMessage() = default;

BlockAnswerMessage::~BlockAnswerMessage() = default;

Element* BlockAnswerMessage::toElement() const {
    ElementObject* e = ElementCreator::object();
    return e->put("block", ElementCreator::create(block))
            ->put("type", ElementCreator::create(type));
}

void BlockAnswerMessage::fromElement(ElementObject* e, const Serializer* serializer, const char* encoding) {
    e->getItem("block", &block);
    e->getItem("type", &type);
}