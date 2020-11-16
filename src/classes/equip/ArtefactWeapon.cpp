#include "include/model/equip/ArtefactWeapon.h"

#include <utility>

ArtefactWeapon::ArtefactWeapon(Level &level, string &fileName, string &name, string &type, string &subType, float x,
                               float y, float w, float h, int state, float damage, map<string, string> properties)
        : Weapon(level, fileName, name, type, subType, x, y, w, h, state, damage) {
    this->changesMapFromXML = std::move(properties);

    for (const auto &p: changesMapFromXML) {
        if (p.first != "damage" && p.first != "state") {
            changesListA.emplace_back(p.first, stof(p.second));
        }
    }
}
