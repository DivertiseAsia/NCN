//
// Created by default on 11/4/2561.
//

#include "MoneyTransaction.h"
#include <utility>
#include "../database/Row.h"

bool MoneyTransaction::operator()() const {
    return true;
}

MoneyTransaction::MoneyTransaction() = default;

Element* MoneyTransaction::toElement() const {
    ElementObject* e = ElementCreator::object();
    e->put("type", ElementCreator::create(get_type()))
                          ->put("amount", ElementCreator::create(amount))
                          ->put("target", ElementCreator::create(target));
    return e;
}

void MoneyTransaction::fromElement(ElementObject* e, const Serializer*, const char*) {
    e->getItem("amount", &amount);
    e->getItem("target", &target);
};

std::string MoneyTransaction::to_string() const {
    std::string res = "amount:" + std::to_string(amount) + " to" + target;
    return res;
}

std::vector<std::string> MoneyTransaction::apply(Row* row){
    auto * cr = dynamic_cast<CustomRow*>(row);
    cr->money -= amount;
    std::vector<std::string> targets;
    targets.push_back(target);
    return  targets;
}

Row* MoneyTransaction::createRow() const {
    return new CustomRow();
};

void MoneyTransaction::apply_reverse(Row* row){
    auto * cr = dynamic_cast<CustomRow*>(row);
    cr->money += amount;
}

bool MoneyTransaction::validate(Row *row) const {
    auto * cr = dynamic_cast<CustomRow*>(row);
    return amount >= cr->money;
}

int MoneyTransaction::get_type() const {
    return 2;
};
std::string MoneyTransaction::description() const {
    return "give money";
};

void MoneyTransaction::fill_data() {
    do {
        std::cout << "Amount of money: " << std::endl;
        std::cin >> amount;
    }while(amount < 0);
    std::cout << "Target key: " << std::endl;
    std::cin >> target;
    std::cout << "Money transaction created" << std::endl;
};

Transaction* MoneyTransaction::clone() {
    return new MoneyTransaction;
}
