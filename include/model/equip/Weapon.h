#include "EnchantedWeapon.h"
#include "Artefact.h"

#pragma once

class Weapon : public EnchantedWeapon, public Artefact {
public:
    string name;

    void getDamage();

    void setDamage();

private:
    int damage;

    void calculateDamage();
};