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

std::vector<std::string> MessagesTransaction::apply(Row* row){
    CustomRow* cr = dynamic_cast<CustomRow*>(row);
    cr->messages.emplace_back(message);
    return std::vector<std::string>();
}

Row* MessagesTransaction::createRow() const {
    return new CustomRow();
};
void MessagesTransaction::apply_reverse(Row* row){

}

bool MessagesTransaction::validate(Row *row) const {
    CustomRow* cr = dynamic_cast<CustomRow*>(row);
    return cr->status.size() > 0;
}