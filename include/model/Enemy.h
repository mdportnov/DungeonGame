#include <utility>

#include "Level.h"
#include "Unit.h"

#pragma once

using namespace sf;

class Enemy : public Unit {
public:
    bool state;
    int dir = 1;
    float lvl;

//    FloatRect getEnemyArea() { return {x - 100, y - 100, w + 100, h + 100}; }

    Enemy(Level &level, string fileName, string name, float x, float y, float w, float h, int layer, float hp, float d, float d1);

    void update(float time) override;

    void checkCollision(int num) override;

    void acceptDamageFrom(Unit *unit) override;
};