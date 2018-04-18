//
// Created by default on 4/4/2561.
//

#include "MessagesTransaction.h"
#include <cstring>

bool MessagesTransaction::operator()() const {
    return true;
}

MessagesTransaction::MessagesTransaction() = default;

Element* MessagesTransaction::toElement() const {
    ElementObject* e = ElementCreator::object();
    return e->put("message", ElementCreator::create(message.c_str()))
            ->put("type", ElementCreator::create(this->get_type()));
}

void MessagesTransaction::fromElement(ElementObject* e, const Serializer*, const char*) {
    e->getItem("message", &message);
};

std::string MessagesTransaction::to_string() const {
    std::string res = "message:" + message;
    return res;
}

std::vector<std::string> MessagesTransaction::apply(Row* row){
    auto * cr = dynamic_cast<CustomRow*>(row);
    cr->messages.emplace_back(message);
    return std::vector<std::string>();
}

Row* MessagesTransaction::createRow() const {
    return new CustomRow();
};

void MessagesTransaction::apply_reverse(Row*){

}

bool MessagesTransaction::validate(Row *row) const {
    auto * cr = dynamic_cast<CustomRow*>(row);
    return !cr->status.empty();
}

int MessagesTransaction::get_type() const {
    return 1;
};

std::string MessagesTransaction::description() const {
    return "New message";
};

void MessagesTransaction::fill_data() {
    std::cout << "New message: " << std::endl;
    std::getline(std::cin, message);
    std::cout << "Message transaction created" << std::endl;
};

Transaction* MessagesTransaction::clone() {
    return new MessagesTransaction;
}
