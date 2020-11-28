#include "include/model/Enemy.h"
#include "include/model/Unit.h"

Enemy::Enemy(Level &level, string fileName, string name, float x, float y, float w, float h, int layer, std::map<string, string> props)
        : Unit(level, fileName, name, x, y, w, h, layer) {
    state = false;
    isAlive = true;
    health = stof(props["hp"]);
    lvl = stof(props["lvl"]);
    damage = stof(props["damage"]);
    speed = stof(props["sp"]);
}

void Enemy::update(float time) {
    Unit::update(time);
    dx = speed * dir;
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

void Enemy::acceptDamageFrom(Unit *unit) {
    health -= unit->calculateDamage(this);
}

