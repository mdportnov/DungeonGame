#include "include/model/equip/ArtefactWeapon.h"

ArtefactWeapon::ArtefactWeapon(Level &level, string &fileName, string &name, string &type, string &subType, float x,
                               float y, float w, float h, int state, float damage,
                               const map<string, string> &properties)
        : Weapon(level, fileName, name, type, subType, x, y, w, h, state, damage) {
    for (const auto &p: properties) {
        if (p.first != "damage" && p.first != "state") {
            changesListA.emplace_back(p.first, stof(p.second));
        }
    }
}

void ArtefactWeapon::draw(RenderWindow &window) {
    Weapon::draw(window);
    Text type;
    type.setPosition(x+10, y+30);
    type.setString("A");
    type.setCharacterSize(12);
    type.setFillColor(Color::Magenta);
    type.setFont(font);
    window.draw(type);
}
