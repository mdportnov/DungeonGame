#include "include/model/ObjectOnField.h"

ObjectOnField::ObjectOnField(Level &level, float x, float y, float w, float h) {
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->level = level;
}

float ObjectOnField::getX() const {
    return x;
}

float ObjectOnField::getY() const {
    return y;
}

