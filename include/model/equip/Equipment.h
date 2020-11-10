#pragma once
#include "include/model/Item.h"

enum class EquipmentTypes {
    HELMET, BREASTPLATE, BOOTS
};

class Equipment : public Item {
public:
//    Equipment(Level &level, string &fileName, string &name, float x, float y, float w, float h, const string &type,
//              int protection, const string &material) : Item(level, fileName, name, x, y, w, h), type(type),
//                                                        protection(protection), material(material) {};


public:
    string type;
    int protection{};
    string material;
};