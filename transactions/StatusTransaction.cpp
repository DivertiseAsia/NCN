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

Element* StatusTransaction::toElement(){
    ElementObject* e = ElementCreator::creator.object();
    ElementCreator::creator.put(e, "status", ElementCreator::creator.create(status.c_str()))
                          ->put(e, "type", ElementCreator::creator.create(0));
    return e;
}

void StatusTransaction::fromElement(ElementObject* e) {
    e->getItem("status", &status);
};
