#pragma once

#include "ObjectOnField.h"

class Item : public ObjectOnField {
public:
    string name, filename;
//    Level level;

    Item(Level &level, std::string &fileName, std::string &name, float x, float y, float w, float h);
//        this->image.loadFromFile("../res/img/" + fileName);
};

