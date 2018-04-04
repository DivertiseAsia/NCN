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

char* MessagesTransaction::serialize() const {
    std::string json("{\"message\": \"");
    json += std::string(message) + std::string("\"};");
    char* v = (char*)malloc((int)json.size());
    strcpy(v, json.c_str());
    return v;
}