#pragma once

#include "ObjectOnField.h"

class Item : public ObjectOnField {
public:
    Item(Level &level, string &fileName, string &name, string &type, string &subType,
         float x, float y, float w, float h, int state);

    enum STATE {
        onMap, onMe, nowhere
    };

    STATE state;
};

