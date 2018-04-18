//
// Created by default on 11/4/2561.
//

#include "Row.h"

Row* CustomRow::clone() const{
    auto r = new CustomRow;
    r->money = money;
    r->status = status;
    r->messages = messages;
    return r;
}

std::string CustomRow::to_string() const {
    std::string str;
    str += "[" + status + "] (value: " + std::to_string(money) + ")\n";
    for(auto& a : messages)
        str += " - " + a + "\n";
    return str;
}

void CustomRow::reward() {
    money += 1;
}