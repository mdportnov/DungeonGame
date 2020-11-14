#include "include/model/equip/Weapon.h"

#include <utility>

Weapon::Weapon(Level &level, string &fileName, string &name, string &type, string &subType, float x, float y, float w,
               float h, int damage, int state) : Item(level, fileName, name, type, subType, x, y, w, h, state) {
    this->damage = damage;
}

float Weapon::getDamage() const {
    return damage;
}
