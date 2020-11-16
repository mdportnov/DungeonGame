#pragma once

#include "include/model/Item.h"

enum EquipmentTypes {
    HELMET, SHIELD, BREASTPLATE
};
enum EquipmentMaterials {
    BRONZE, GOLD, DIAMOND
};

class Equipment : public Item {
public:
    Equipment(Level &level, string &fileName, string &name, string &type, string &subType,
              float x, float y, float w, float h, int state, float protection, int eqType,
              int materialType);

    void draw(RenderWindow &window) override;

    float protection;
    int eqType;
    int materialType;
};
