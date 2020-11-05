#include "include/model/Item.h"
#pragma once

enum class EquipmentTypes {
    HELMET, BREASTPLATE, BOOTS
};

class Equipment : public Item {
public:
    explicit Equipment(const string &name) : Item(name) {

    }

    Equipment() = default;

    string type;
    int protection{};
    string material;
};