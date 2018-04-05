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
char* StatusTransaction::serialize() const {
    std::string json("{\"status\": \"");
    json += std::string(status) + std::string("\"};");
    char* v = (char*)malloc((int)json.size());
    strcpy(v, json.c_str());
    return v;
}
