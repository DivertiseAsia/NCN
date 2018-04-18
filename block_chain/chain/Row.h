//
// Created by default on 11/4/2561.
//

#ifndef BLOCK_CHAIN_ROW_H
#define BLOCK_CHAIN_ROW_H


#include <string>

class Row {
public:
    virtual ~Row() = default;
    virtual Row* clone() const = 0;
    virtual std::string to_string() const = 0;
    virtual void reward() = 0;
};


#endif //BLOCK_CHAIN_ROW_H
