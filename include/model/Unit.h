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
    float dx, dy, speed;
    float health, defaultDamage;
    int framesCount = 0;
    double currentFrame = 0;
    bool isAlive;
    std::vector<MapObject> map; //вектор тайлов карты
    std::vector<MapObject> objects; //вектор персонажей, предметов карты

    std::string name;

    Unit(Level &level, string &fileName,
         string &name, float x, float y, float w, float h);

    void update(float time) override;

    virtual void checkCollision(int num);

    virtual void acceptDamageFrom(Unit *unit);

    virtual void draw(RenderWindow &window);

    virtual float calculateDamage(Unit *unit);
};