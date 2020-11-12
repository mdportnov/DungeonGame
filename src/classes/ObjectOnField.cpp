#include "include/model/ObjectOnField.h"

ObjectOnField::ObjectOnField(Level &level, string &fileName, string &name, float x, float y, float w, float h) {
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->level = level;
    this->name = name;
    this->image.loadFromFile("../res/img/" + fileName);
    texture.loadFromImage(image);
    sprite.setTexture(texture);
    sprite.setTextureRect(IntRect(0, 0, w, h));
}

float ObjectOnField::getX() const {
    return x;
}

float ObjectOnField::getY() const {
    return y;
}

void ObjectOnField::update(float time) {
    sprite.setPosition(x, y);
}

