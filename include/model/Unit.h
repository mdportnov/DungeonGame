#pragma once

#include <include/model/equip/Weapon.h>
#include "include/main.h"
#include "Level.h"
#include "ObjectOnField.h"
#include "MapObject.h"

using namespace sf;
using namespace std;

class Unit : public ObjectOnField {
public:
    std::map<string, float> attributes;
    float dx, dy, speed;
    float health, damage;
    int framesCount = 0;
    double currentFrame = 0;
    bool isAlive;
    std::vector<MapObject> map; //вектор тайлов карты

    std::string name;

    Unit(Level &level, string &fileName,
         string &name, float x, float y, float w, float h, int layer);

    void update(float time) override;

    virtual void checkCollision(int num);

    virtual void acceptDamageFrom(Unit *unit);

    virtual void draw(RenderWindow &window);

    virtual float calculateDamage(Unit *unit);
};