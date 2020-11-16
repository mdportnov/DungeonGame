#include "include/model/equip/EnchantedWeapon.h"

#include <utility>

EnchantedWeapon::EnchantedWeapon(Level &level, string &fileName, string &name, string &type, string &subType, float x,
                                 float y, float w, float h, int state, float damage, map<string, string> properties)
        : Weapon(level, fileName, name, type, subType, x, y, w, h, state, damage) {
    this->changesMapFromXML = std::move(properties);

    for (const auto &p: changesMapFromXML) {
        if (p.first != "damage" && p.first != "state" && p.first.length() > 2) {
            changesListE.insert({p.first, stof(p.second)});
        }
    }
}

float EnchantedWeapon::calculateDamage(string &enemyType) {
    for (const auto &list: changesListE) {
        if (list.first == enemyType) {
            return getDamage() * list.second;
        }
    }
    return getDamage();
}




