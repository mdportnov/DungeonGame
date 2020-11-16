#include <utility>

#include "Level.h"
#include "Unit.h"

#pragma once

using namespace sf;

class Enemy : public Unit {
public:
    bool state;
    int dir = 1;

    //ф-ция получения поля зрения врага
    FloatRect getEnemyArea() { return {x - 100, y - 100, w + 100, h + 100}; }

    Enemy(Level &level, std::string fileName, std::string name,
          float x, float y, float w, float h);

    void update(float time) override;

    void checkCollision(int num) override;

    void acceptDamageFrom(Unit *unit) override;
};