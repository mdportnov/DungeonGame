#pragma once

#include "vector"
#include "utility"
#include "string"
#include "ChangesAttributes.h"

using namespace std;

#include "Equipment.h"

/**
 * Класс артефактного оружия, величивающего определённые характеристики героя
 */

class ArtefactEquipment : public Equipment, public ChangesAttributes {
public:
    ArtefactEquipment(Level &level, string &fileName, string &name, string &type, string &subType, float x, float y,
                      float w, float h, int layer, int state, float protection, int eqType, int materialType,
                      const map<string, string> &properties);

    void draw(RenderWindow &window) override;

};
