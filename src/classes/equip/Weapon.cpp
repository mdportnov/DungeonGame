#include "include/model/equip/Weapon.h"

Weapon::Weapon(Level &level, string &fileName, string &name, string &type, string &subType, float x, float y, float w,
               float h, int layer, int state, float damage) : Item(level, fileName, name, type, subType, x, y, w, h,
                                                                   layer, state) {
    this->damage = damage;
}

float Weapon::getDamage() const {
    return damage;
}

void Weapon::draw(RenderWindow &window) {
    ObjectOnField::draw(window);
}

Weapon::~Weapon() = default;


