//
// Created by default on 4/4/2561.
//

#include "StatusTransaction.h"

bool operator()() const {
    return true;
}

StatusTransaction::StatusTransaction(std::string str): status(str) {

}