#include <utility>

#include "Level.h"

#pragma once

using namespace sf;

class Enemy : public Unit {
public:
    bool state;

    FloatRect getEnemyView() { //ф-ция получения поля зрения врага
        return {x, y, w + 500, h + 500};
    }

    Enemy(Level level, std::string fileName, std::string name,
          float x, float y, float w, float h) : Unit(level, fileName, name, x, y, w, h) {
        state = false;
        isAlive = true;
        health = 100;
        map=level.getAllMapObjects();
    }

    Enemy(Level level, Sprite &sprite, std::string name,
          float x, float y, float w, float h) : Unit(level, sprite, name, x, y, w, h) {
        state = false;
        isAlive = true;
        health = 100;
        map=level.getAllMapObjects();
    }

    void update(float time) override {
        Unit::update(time);
        x += dx * time;
//        timer += time;
//        if (time > 3500) {
//            dx *= -1;
//            timer = 0;
//        }
//        Unit::checkCollision(1);
//        Unit::checkCollision(0);
//        if (name == "egorov") {
//            dx=0.01;
//            dy=0.01;
//            checkCollision(1);
//            x += dx * time;
//            checkCollision(0);
//            y += dy * time;
//            sprite.setPosition(x + w / 2, y + h / 2);
//            if (health <= 0) isAlive = false;
//        }
    }

    void pursueHero();

    void kickStudent();
};