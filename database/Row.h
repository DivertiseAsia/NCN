//
// Created by default on 11/4/2561.
//

#ifndef BLOCK_CHAIN_CUSTOM_ROW_H
#define BLOCK_CHAIN_CUSTOM_ROW_H

#include "../block_chain/chain/state/Row.h"
#include <string>
#include <vector>

/**
 *  @class CustomRow "database/Row.h"
 *  A custom Row for testing
 *  @see Serializer
 *
 *  @author Mathieu Lochet
 *  @version 2
 */
class CustomRow: public Row {
    friend class StatusTransaction;
    friend class MessagesTransaction;
    friend class MoneyTransaction;
public:
    ~CustomRow() override = default;
    Row* clone() const override;
    std::string to_string() const override;
    void reward() override;
private:
    double money;
    std::string status;
    std::vector<std::string> messages;
};


#endif //BLOCK_CHAIN_CUSTOM_ROW_H
