#include <include/model/Item.h>
#include "EnchantedWeapon.h"
#include "Artefact.h"

#pragma once

class Weapon{
public:
    string name;

    explicit Weapon(string name);

    void getDamage();

    void setDamage();

private:
    int damage;

    void calculateDamage();
};