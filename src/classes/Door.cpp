#include "include/model/Door.h"

Door::Door(Level &level, string &fileName, string &name,
           float x, float y, float w, float h) : ObjectOnField(level, fileName, name, x, y, w, h) {
    isLocked = true;
}

void Door::update() {
    sprite.setPosition(x, y);
}

FloatRect Door::getAreaRect() {
    return {x - 50, y - 50, w + 100, h + 100};
}

void Door::changeDoorState() {
    if (isLocked) {
        isLocked = false;
        this->image.loadFromFile("../res/img/door_opened.png");

    } else {
        isLocked = true;
        this->image.loadFromFile("../res/img/door_closed.png");
    }
    texture.loadFromImage(image);
    sprite.setTexture(texture);
    sprite.setTextureRect(IntRect(0, 0, w, h));
}

