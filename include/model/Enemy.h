#include <utility>

#include "Level.h"

#pragma once

using namespace sf;

class Enemy : public Unit {
public:
    bool state;

    Enemy(Level level, std::string fileName, std::string name,
          float x, float y, float w, float h) : Unit(level, fileName, name, x, y, w, h) {
        state = false;
        isAlive = true;
    }

    void update(float time) override {
        Unit::update(time);
        if (name == "egorov") {
            checkCollision(1);
            x += dx * time;
            sprite.setPosition(x + w / 2, y + h / 2);
            if (health <= 0) isAlive = false;
        }
    }

    void pursueHero();

    void kickStudent();
};