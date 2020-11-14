#include "include/model/Chest.h"

Chest::Chest(Level &level, string &fileName, string &name,
             float x, float y, float w, float h, int lockLevel, bool isLocked) : ObjectOnField(level, fileName, name, x,
                                                                                               y, w, h) {
    this->lockLevel = lockLevel;
    this->isLocked = isLocked;
    if(!isLocked){
        this->image.loadFromFile("../res/img/chest_opened.png");
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setTextureRect(IntRect(0, 0, w, h));
    }
}

FloatRect Chest::getAreaRect() {
    return {x - 50, y - 50, w + 100, h + 100};
}

bool Chest::open(Player &player) {
    if (true) {
        this->image.loadFromFile("../res/img/chest_opened.png");
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setTextureRect(IntRect(0, 0, w, h));
        isLocked = false;
        return true;
    }
    return false;
}
