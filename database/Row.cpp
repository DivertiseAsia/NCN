//
// Created by default on 11/4/2561.
//

#include "Row.h"

Row* CustomRow::clone() const{
    CustomRow* r = new CustomRow;
    r->money = money;
    r->status = status;
    r->messages = messages;
    return r;
}