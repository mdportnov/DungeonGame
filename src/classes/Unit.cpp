#include "include/model/Unit.h"
#include "include/model/ObjectOnField.h"

Unit::Unit(Level &level, string &fileName, string &name,
           float x, float y, float w, float h, int layer) : ObjectOnField(level, fileName, name, x, y, w, h, layer) {
    this->map = level.getAllStaticObjects();
    this->name = name;
    isAlive = true;
    health = 100;

    dx = 0;
    dy = 0;
    speed = 0;
}

float Unit::calculateDamage(Unit *unit) {
    return damage;
}

void Unit::update(float time) {
    x += dx * time;
    checkCollision(0);

    y += dy * time;
    checkCollision(1);

    ObjectOnField::update(time);

    if (health <= 0) {
        isAlive = false;
        speed = 0;
    }
}

void Unit::checkCollision(int axis) {
    for (auto &i : map)
        if (getRect().intersects(i.rect)) {
            if (i.name == "solid") {
                if (dy > 0 && axis == 1) {
                    y = i.rect.top - h;
                    dy = 0;
                }
                if (dy < 0 && axis == 1) {
                    y = i.rect.top + i.rect.height;
                    dy = 0;
                }
                if (dx > 0 && axis == 0) { x = i.rect.left - w; }
                if (dx < 0 && axis == 0) { x = i.rect.left + i.rect.width; }
            }
        }
}

void Unit::acceptDamageFrom(Unit *unit) {
    health -= unit->calculateDamage(this);
}

void Unit::draw(RenderWindow &window) {
    window.draw(sprite);
}
