#include "include/model/equip/EnchantedArtefactWeapon.h"


EnchantedArtefactWeapon::EnchantedArtefactWeapon(Level &level, string &fileName, string &name, string &type,
                                                 string &subType, float x, float y, float w, float h, int state,
                                                 float damage, const map<string, string> &properties)
        : ArtefactWeapon(level, fileName, name, type, subType, x, y, w, h, state, damage, properties),
          EnchantedWeapon(level, fileName, name, type, subType, x, y, w, h, state, damage, properties),
          Weapon(level, fileName, name, type, subType, x, y, w, h, state, damage) {
}

void EnchantedArtefactWeapon::draw(RenderWindow &window) {
    EnchantedWeapon::draw(window);
    Text type;
    type.setPosition(x, y);
    type.setString("EA");
    type.setPosition(x + 10, y + 30);
    type.setCharacterSize(12);
    type.setFillColor(Color::Red);
    type.setFont(font);
    window.draw(type);
}
