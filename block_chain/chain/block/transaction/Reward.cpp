//
// Created by default on 19/4/2561.
//

#include "Reward.h"
/*
bool Reward::operator()() const {
    return true;
}
*/
Reward::Reward() = default;

Element* Reward::toElement() const {
    return nullptr;
}

void Reward::fromElement(ElementObject*, const Serializer*, const char*) {
}

void Reward::apply_reverse(Row*){

}

bool Reward::validate(Row*) const {
    return true;
}

int Reward::get_type() const {
    return -1;
};

std::string Reward::description() const {
    return "";
};

void Reward::fill_data() {
};

std::vector<std::string> Reward::apply(Row* row){
    row->reward();
    return std::vector<std::string>();
}