#include "include/model/Door.h"

Door::Door(Level &level, string &fileName, string &name, float x, float y, float w, float h) : ObjectOnField(level, x,
                                                                                                             y, w, h) {
    this->image.loadFromFile("../res/img/" + fileName);
    texture.loadFromImage(image);
    sprite.setTexture(texture);
    sprite.setTextureRect(IntRect(0, 0, w, h));
}

void Door::update(float time) {
    sprite.setPosition(x, y);
}

