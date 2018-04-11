//
// Created by default on 4/4/2561.
//

#include "MessagesTransaction.h"
#include <cstring>

bool MessagesTransaction::operator()() const {
    return true;
}

MessagesTransaction::MessagesTransaction(std::string str): message(std::move(str)) {

}

MessagesTransaction::MessagesTransaction() = default;

Element* MessagesTransaction::toElement() const {
    ElementObject* e = ElementCreator::creator.object();
    ElementCreator::creator.put(e, "message", ElementCreator::creator.create(message.c_str()))
                          ->put(e, "type", ElementCreator::creator.create(1));
    return e;
}

void MessagesTransaction::fromElement(ElementObject* e, const Serializer*, const char* encoding) {
    e->getItem("message", &message);
};

std::string MessagesTransaction::to_string() const {
    std::string res = "message:" + message;
    return res;
}

void MessagesTransaction::apply(){

}