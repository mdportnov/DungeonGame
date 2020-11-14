#include <include/model/Item.h>
#include "EnchantedWeapon.h"
#include "Artefact.h"

#pragma once

class Weapon : public Item {
public:
    Weapon(Level &level, string &fileName, string &name, string &type, string &subType,
           float x, float y, float w, float h, int state, float damage);

    float getDamage() const;

private:
    float damage;

    void calculateDamage();
};