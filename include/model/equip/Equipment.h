#pragma once

#include "include/model/Item.h"

/**
 * Класс, отвечающий за броню, одетую на персонажа
 */

class Equipment : public Item {
public:
    Equipment(Level &level, string &fileName, string &name, string &type, string &subType,
              float x, float y, float w, float h, int layer, int state, float protection, int eqType,
              int materialType);

    void draw(RenderWindow &window) override;

    float protection;
    int eqType;
    int materialType;
};
