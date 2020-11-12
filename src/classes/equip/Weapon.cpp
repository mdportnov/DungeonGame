#include "include/model/equip/Weapon.h"

#include <utility>

Weapon::Weapon(Level &level, string &fileName, string &name, string &type, string &subType, float x, float y, float w,
               float h, int damage) : Item(level, fileName, name, type, subType, x, y, w, h) {
    this->damage = damage;
}

int Weapon::getDamage() const {
    return damage;
}
