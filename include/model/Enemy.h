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

    Enemy(Level &level, string fileName, string name, float x, float y, float w, float h, int layer, std::map<string, string> props);

    void update(float time) override;

    void checkCollision(int num) override;

    void acceptDamageFrom(Unit *unit) override;
};