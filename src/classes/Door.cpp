#include "include/model/Door.h"

Door::Door(Level &level, string &fileName, string &name,
           float x, float y, float w, float h) : ObjectOnField(level, fileName, name, x, y, w, h) {
    isLocked = true;

}

void Door::update(float time) {
    sprite.setPosition(x, y);
}

