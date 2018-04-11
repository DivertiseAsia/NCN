//
// Created by default on 11/4/2561.
//

#ifndef BLOCK_CHAIN_CUSTOM_ROW_H
#define BLOCK_CHAIN_CUSTOM_ROW_H

#include "../block_chain/chain/Row.h"
#include <string>
#include <vector>

class CustomRow: public Row {
    friend class StatusTransaction;
    friend class MessagesTransaction;
    friend class MoneyTransaction;
public:
    virtual ~CustomRow() {};
private:
    double money;
    std::string status;
    std::vector<std::string> messages;
};


#endif //BLOCK_CHAIN_CUSTOM_ROW_H
