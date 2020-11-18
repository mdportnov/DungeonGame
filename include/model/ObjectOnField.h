#pragma once

#include "Level.h"

using namespace sf;

class ObjectOnField {
public:
    float x, y, w, h;
    Texture texture;
    Sprite sprite;
    Level level;
    Image image;
    string fileName;
    string type;
    string subType;
    string name;
    Font font;
    virtual FloatRect getRect() { return {x, y, w, h}; }

    ObjectOnField(Level &level, string &fileName, string &name, float x, float y, float w, float h);

    virtual void draw(RenderWindow &window);

    float getX() const;

    float getY() const;

    virtual void update(float time);
};