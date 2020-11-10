#include "ObjectOnField.h"
#include "Level.h"

#pragma once

class Item : public ObjectOnField {
public:
    string name, filename;

    Item(Level level, std::string &fileName, std::string &name, float x, float y, float w, float h);

//        this->image.loadFromFile("../res/img/" + fileName);

};

