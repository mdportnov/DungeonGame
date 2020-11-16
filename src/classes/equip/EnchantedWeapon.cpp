#include "include/model/equip/EnchantedWeapon.h"

EnchantedWeapon::EnchantedWeapon(Level &level, string &fileName, string &name, string &type, string &subType, float x,
                                 float y, float w, float h, int state, float damage,
                                 const map<string, string> &properties)
        : Weapon(level, fileName, name, type, subType, x, y, w, h, state, damage) {
    for (const auto &p: properties) {
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

void EnchantedWeapon::draw(RenderWindow &window) {
    Weapon::draw(window);
    Text type;
    type.setPosition(x+10, y+30);
    type.setString("E");
    type.setCharacterSize(12);
    type.setFillColor(Color::Cyan);
    type.setFont(font);
    window.draw(type);
}





