//
// Created by default on 25/4/2561.
//

#include "Framework.h"
#include "utils/serialization/Serializer.h"

Framework::Framework(): manager(), serializer(nullptr) {

};

Framework::~Framework(){
    delete serializer;
    transactions.clear();
}

void Framework::add_transaction(Transaction* transaction){
    transactions.emplace_back(transaction);
}

const TransactionManager Framework::generate_manager(){
    for(auto t : transactions)
        manager.put(t);
    return manager;
}

Serializer* Framework::generate_serializer(){
    delete serializer;
    serializer = new Serializer;
    for(auto t : transactions)
        serializer->add_transaction(t->get_type(), [t]() -> Transaction*{return t->clone();});
    return serializer;
}