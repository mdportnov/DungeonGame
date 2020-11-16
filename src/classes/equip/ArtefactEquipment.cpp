#include "include/model/equip/ArtefactEquipment.h"

#include <utility>

ArtefactEquipment::ArtefactEquipment(Level &level, string &fileName, string &name, string &type, string &subType,
                                     float x, float y, float w, float h, int state, float protection, int eqType,
                                     int materialType, map<string, string> properties) : Equipment(
        level, fileName, name, type, subType, x, y, w, h, state, protection, eqType, materialType),
                                                                                         changesMapFromXML(std::move(
                                                                                                 properties)) {
    for (const auto &p: changesMapFromXML) {
        if (p.first.length() == 2) {
            changesListA.emplace_back(p.first, stof(p.second));
        }
    }

}

void ArtefactEquipment::draw(RenderWindow &window) {
    Equipment::draw(window);
    Text type;
    type.setPosition(x + 10, y + 30);
    type.setString("A");
    type.setCharacterSize(12);
    type.setFillColor(Color::Magenta);
    type.setFont(font);
    window.draw(type);
}
