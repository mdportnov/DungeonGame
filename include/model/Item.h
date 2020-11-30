#pragma once

#include "ObjectOnField.h"

/**
 * Класс предмета, лежащего в инвентаре, на карте или в сундуке
 */
class Item : public ObjectOnField {
public:
    Item(Level &level, string &fileName, string &name, string &type, string &subType,
         float x, float y, float w, float h, int layer, int state);

    enum STATE {
        onMap, onMe, inChest, nowhere
    };

    STATE state;

    FloatRect getRect() override;
};

