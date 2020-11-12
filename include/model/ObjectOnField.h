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
    string fileName;
    string type;
    string subType;
    string name;

    // для проверки столкновений
    virtual FloatRect getRect() { return {x, y, w, h}; }

    ObjectOnField(Level &level, string &fileName, string &name, float x, float y, float w, float h);

    float getX() const;

    float getY() const;

    virtual void update(float time);
};