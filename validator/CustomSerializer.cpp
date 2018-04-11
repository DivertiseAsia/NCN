#include "CustomSerializer.h"

#include <iostream>
Transaction* CustomSerializer::unserializeTransaction(std::string transaction, const char* key) const {
    ElementObject* e = getElement(transaction, key);
    int type;
    e->getItem("type", &type);
    Transaction* t;
    if(!type)
        t = new StatusTransaction();
    else
        t = new MessagesTransaction();
    t->__init__(e, this, key);
    return t;
}
