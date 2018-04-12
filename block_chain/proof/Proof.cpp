//
// Created by default on 12/4/2561.
//

#include "Proof.h"
#include "ProofOfStake.h"
#include "ProofOfWork.h"
#include "ProofOfHold.h"
#include "ProofOfImportance.h"
#include "ProofOfMinimumAgedStake.h"
#include "ProofOfStakeTime.h"
#include "ProofOfUse.h"

const int Proof::WORK = 0;
const int Proof::STAKE = 1;
const int Proof::HOLD = 2;
const int Proof::IMPORTANCE = 3;
const int Proof::MINIMUM_AGED_STAKE = 4;
const int Proof::STAKE_TIME = 5;
const int Proof::USE = 6;
std::map<int, std::function<Proof*()>> Proof::items;


Proof* Proof::generate(const int type) {
    if(items.empty()) {
        items[Proof::WORK] = []() -> Proof*{return new ProofOfWork();};
        items[Proof::STAKE] = []() -> Proof*{return new ProofOfStake;};
        items[Proof::HOLD] = []() -> Proof*{return new ProofOfHold;};
        items[Proof::IMPORTANCE] = []() -> Proof*{return new ProofOfImportance;};
        items[Proof::MINIMUM_AGED_STAKE] = []() -> Proof*{return new ProofOfMinimumAgedStake;};
        items[Proof::STAKE_TIME] = []() -> Proof*{return new ProofOfStakeTime;};
        items[Proof::USE] = []() -> Proof*{return new ProofOfUse;};
    }
    return (items.find(type)->second)();
}