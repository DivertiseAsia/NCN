//
// Created by default on 4/4/2561.
//

#include "StatusTransaction.h"
#include <iostream>
#include <cstring>
#include <cstdlib>

bool StatusTransaction::operator()() const {
    return true;
}

StatusTransaction::StatusTransaction(std::string str): status(str) {

}

StatusTransaction::StatusTransaction() = default;

Element* StatusTransaction::toElement() const {
    ElementObject* e = ElementCreator::creator.object();
    ElementCreator::creator.put(e, "type", ElementCreator::creator.create(0))
            ->put(e, "status", ElementCreator::creator.create(status.c_str()));
    return e;
}

void StatusTransaction::fromElement(ElementObject* e, const Serializer*, const char* encoding) {
    e->getItem("status", &status);
};

std::string StatusTransaction::to_string() const {
    std::string res = "status:" + status;
    return res;
}

void StatusTransaction::apply(){
    Row* row;
    row->action = "status";
    row->value = status;
}