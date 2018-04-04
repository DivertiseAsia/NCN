//
// Created by default on 4/4/2561.
//

#include "MessagesTransaction.h"

bool operator()() const {
    return true;
}

MessagesTransaction::MessagesTransaction(std::string str): message(str) {

}