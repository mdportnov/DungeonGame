#include "include/model/equip/ArtefactEquipment.h"

ArtefactEquipment::ArtefactEquipment(Level &level,
                                     string &fileName, string &name, string &type, string &subType, float x,
                                     float y, float w, float h, int layer, int state, float protection, int eqType,
                                     int materialType, const map<string, string> &properties) :
        ChangesAttributes(properties),
        Equipment(level, fileName, name, type, subType, x, y, w, h, layer, state, protection, eqType, materialType) {
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
