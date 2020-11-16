#pragma once

#include "vector"
#include "utility"
#include "string"
#include "Weapon.h"

using namespace std;

class EnchantedWeapon : public Weapon {
public:
    EnchantedWeapon(Level &level, string &fileName, string &name, string &type, string &subType, float x, float y,
                    float w, float h, int state, float damage, map<string, string> properties);

    map<string, string> changesMapFromXML;
    map<string, float> changesListE;

    float calculateDamage(string &enemyType);
};