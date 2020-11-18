#pragma once

#include "vector"
#include "utility"
#include "string"
#include "Weapon.h"

using namespace std;

class EnchantedWeapon : virtual public Weapon {
public:
    EnchantedWeapon(Level &level, string &fileName, string &name, string &type, string &subType, float x, float y,
                    float w, float h, int layer, int state, float damage, const map<string, string> &properties);

    map<string, float> changesListE;

    float calculateDamage(string &enemyType);

    void draw(RenderWindow &window);
};