#pragma once

#include "Level.h"

using namespace sf;

class ObjectOnField {
public:
    float x{}, y{}, w{}, h{};
    Texture texture;
    Sprite sprite;
    Level level;
    Image image;

    ObjectOnField(Level &level, float x, float y, float w, float h);

    float getX() const;

    float getY() const;
};