//
// Created by default on 11/4/2561.
//

#include "MoneyTransaction.h"
#include "../database/Row.h"

bool MoneyTransaction::operator()() const {
    return true;
}

MoneyTransaction::MoneyTransaction(int a, std::string str): amount(a), target(str) {

}

MoneyTransaction::MoneyTransaction() = default;

Element* MoneyTransaction::toElement() const {
    ElementObject* e = ElementCreator::creator.object();
    ElementCreator::creator.put(e, "type", ElementCreator::creator.create(2))
                          ->put(e, "amount", ElementCreator::creator.create(amount))
                          ->put(e, "target", ElementCreator::creator.create(target));
    return e;
}

void MoneyTransaction::fromElement(ElementObject* e, const Serializer*, const char* encoding) {
    e->getItem("amount", &amount);
    e->getItem("target", &target);
};

std::string MoneyTransaction::to_string() const {
    std::string res = "amount:" + std::to_string(amount) + " to" + target;
    return res;
}

std::vector<std::string> MoneyTransaction::apply(Row* row){
    CustomRow* cr = dynamic_cast<CustomRow*>(row);
    cr->money -= amount;
    std::vector<std::string> targets;
    targets.push_back(target);
    return  targets;
}

Row* MoneyTransaction::createRow() const {
    return new CustomRow();
};

void MoneyTransaction::apply_reverse(Row* row){
    CustomRow* cr = dynamic_cast<CustomRow*>(row);
    cr->money += amount;
}

bool MoneyTransaction::validate(Row *row) const {
    CustomRow* cr = dynamic_cast<CustomRow*>(row);
    return amount >= cr->money;
}
