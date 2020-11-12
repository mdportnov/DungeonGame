#pragma once

#include <include/model/ObjectOnField.h>

class Door : public ObjectOnField {
public:
    bool isLocked;

    FloatRect getAreaRect();

    Door(Level &level, string &fileName, string &name, float x, float y, float w, float h);

    void update();

    void changeDoorState();
};