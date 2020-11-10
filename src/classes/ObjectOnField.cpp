#include "include/model/ObjectOnField.h"

ObjectOnField::ObjectOnField(float x, float y, float w, float h, Level &level) {
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->level = level;
}