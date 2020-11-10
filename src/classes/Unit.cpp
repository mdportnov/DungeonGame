#include "include/model/Unit.h"

Unit::Unit(Level &level, string &fileName, string &name, float x, float y, float w, float h) : ObjectOnField(x, y, w, h,
                                                                                                             level) {
    this->level = level;
    this->name = name;
    this->image.loadFromFile("../res/img/" + fileName);
    objects = level.getAllObjects();
    this->map = level.getAllMapObjects();

    isAlive = true;
    health = 100;

    dx = 0;
    dy = 0;
    speed = 0;
    texture.loadFromImage(image);
    sprite.setTexture(texture);
    sprite.setTextureRect(IntRect(0, 0, w, h));

}

void Unit::update(float time) {
    x += dx * time;
    checkCollision(0);

    y += dy * time;
    checkCollision(1);
    sprite.setPosition(x, y);

    if (health <= 0) {
        isAlive = false;
        speed = 0;
    }
}

void Unit::checkCollision(int num) {
    for (auto &i : map)
        if (getRect().intersects(i.rect)) {
            if (i.name == "solid") {
                if (dy > 0 && num == 1) {
                    y = i.rect.top - h;
                    dy = 0;
                }
                if (dy < 0 && num == 1) {
                    y = i.rect.top + i.rect.height;
                    dy = 0;
                }
                if (dx > 0 && num == 0) { x = i.rect.left - w; }
                if (dx < 0 && num == 0) { x = i.rect.left + i.rect.width; }
            }
        }
}
