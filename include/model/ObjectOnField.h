#include "include/main.h"
#include "Level.h"
#pragma once

using namespace sf;

class ObjectOnField {
public:
    float x, y, w, h;
    Texture texture;
    Sprite sprite;
    Level level;

    ObjectOnField(float x, float y, float w, float h, Level &level);

    float getX() const { return x; }

    float getY() const { return y; }
};