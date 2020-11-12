#pragma once

#include "ObjectOnField.h"

class Item : public ObjectOnField {
public:
    Item(Level &level, string &fileName, string &name, string &type, string &subType,
         float x, float y, float w, float h);

    virtual void doNothing();

    enum STATE {
        onMap, onMe, nowhere
    };

//    bool onMap = true;
    STATE state = onMap;
};

