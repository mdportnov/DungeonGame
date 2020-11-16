#include <include/model/Player.h>
#include <include/model/equip/EnchantedWeapon.h>
#include "include/model/Enemy.h"
#include "include/model/Unit.h"

Enemy::Enemy(Level &level, std::string fileName, std::string name,
             float x, float y, float w, float h, float xp) : Unit(level, fileName, name, x, y, w, h) {
    state = false;
    isAlive = true;
    health = xp;
    defaultDamage = 10;
    objects = level.getAllDynamicObjects();
    this->map = level.getAllStaticObjects();
    speed = 0.1;
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

