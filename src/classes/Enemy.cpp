#include "include/model/Enemy.h"

Enemy::Enemy(Level &level, std::string fileName, std::string name,
             float x, float y, float w, float h) : Unit(level, fileName, name, x, y, w, h) {
    state = false;
    isAlive = true;
    health = 100;
    objects = level.getAllObjects();
    this->map = level.getAllMapObjects();
    start_x = x;
    start_y = y;
    speed = 0.05;
}

void Enemy::update(float time) {
    Unit::update(time);

    dx = speed * dir;
//        if (getRect().intersects(level.get)){
//
//        }
}

void Enemy::checkCollision(int num) {
    for (auto &i : map)
        if (getRect().intersects(i.rect)) {
            if (i.name == "solid") {
                if (dx > 0 && num == 0) {
                    dir *= -1;
                    x = i.rect.left - w;

                    sprite.setOrigin({30, 0});
                    sprite.setScale({float(dir) * 1, 1});
                }
                if (dx < 0 && num == 0) {
                    dir *= -1;
                    x = i.rect.left + i.rect.width + w;
                    sprite.setOrigin({30, 0});
                    sprite.setScale({float(dir) * 1, 1});
                }
                if (dy > 0 && num == 1) {
                    y = i.rect.top - h;
                    dy = 0;
                }
                if (dy < 0 && num == 1) {
                    y = i.rect.top + i.rect.height;
                    dy = 0;
                }
            }
        }

}

