#pragma once

#include "Level.h"

using namespace sf;

class ObjectOnField {
public:
    string fileName, type, subType, name;
    float x, y, w, h;
    int layer;
    Texture texture;
    Sprite sprite;
    Level level;
    Image image;
    Font font;

    virtual FloatRect getRect() { return {x, y, w, h}; }

    ObjectOnField(Level &level, string &fileName, string &name, float x, float y, float w, float h, int layer);

    virtual void draw(RenderWindow &window);

    float getX() const;

    float getY() const;

    virtual void update(float time);
};