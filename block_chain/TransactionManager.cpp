//
// Created by default on 12/4/2561.
//

#include "TransactionManager.h"

TransactionManager::TransactionManager() = default;

void TransactionManager::put(Transaction* t) {
    transactions[t->get_type()] = t;
}

Transaction* TransactionManager::run(){
    int chosen;
    std::cout << "Chose a transaction type: " << std::endl;
    for(auto a : transactions)
        std::cout << a.first << " - " << a.second->description() << std::endl;
    std::cin >> chosen;
    std::string str;
    getline(std::cin, str);
    auto a = transactions.find(chosen);
    if(a != transactions.end()){
        Transaction* t = a->second->clone();
        t->fill_data();
        return t;
    }
    if(chosen == -1)
        return (Transaction*)-1;
    return nullptr;
}

TransactionManager::~TransactionManager() {
    transactions.clear();
}
