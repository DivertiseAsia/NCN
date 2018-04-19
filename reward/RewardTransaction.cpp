//
// Created by default on 19/4/2561.
//

#include "RewardTransaction.h"
#include "../database/Row.h"


RewardTransaction::RewardTransaction() = default;

Row* RewardTransaction::createRow() const {
    return new CustomRow();
};


Transaction* RewardTransaction::clone() {
    return new RewardTransaction;
}
