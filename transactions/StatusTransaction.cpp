//
// Created by default on 4/4/2561.
//

#include "StatusTransaction.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <utility>

bool StatusTransaction::operator()() const {
    return true;
}

StatusTransaction::StatusTransaction() = default;

Element* StatusTransaction::toElement() const {
    ElementObject* e = ElementCreator::object();
    return e->put("type", ElementCreator::create(get_type()))
            ->put("status", ElementCreator::create(status.c_str()));
}

void StatusTransaction::fromElement(ElementObject* e, const Serializer*, const char*) {
    e->getItem("status", &status);
};

std::string StatusTransaction::to_string() const {
    std::string res = "status:" + status;
    return res;
}

std::vector<std::string> StatusTransaction::apply(Row* row){
    auto * cr = dynamic_cast<CustomRow*>(row);
    cr->status = status;
    return  std::vector<std::string>();
}

Row* StatusTransaction::createRow() const {
    return new CustomRow();
};

void StatusTransaction::apply_reverse(Row*){

}

bool StatusTransaction::validate(Row*) const {
    return true;
}

int StatusTransaction::get_type() const {
    return 0;
};

std::string StatusTransaction::description() const {
    return "status update";
};


void StatusTransaction::fill_data() {
    std::cout << "New status: " << std::endl;
    std::getline(std::cin, status);
    std::cout << "Status transaction created" << std::endl;
};

Transaction* StatusTransaction::clone() {
    return new StatusTransaction;
}
