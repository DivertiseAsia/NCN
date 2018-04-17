//
// Created by default on 11/4/2561.
//

#ifndef BLOCK_CHAIN_ROW_H
#define BLOCK_CHAIN_ROW_H


class Row {
public:
    virtual ~Row() = default;
    virtual Row* clone() const = 0;
};


#endif //BLOCK_CHAIN_ROW_H
