#pragma once

#include "include/main.h"
#include "Level.h"
#include "ObjectOnField.h"
#include "MapObject.h"

using namespace sf;
using namespace std;

class Unit : public ObjectOnField {
public:
    float dx, dy, speed, health;
    int framesCount = 0;
    double currentFrame = 0;
    bool isAlive;
    std::vector<MapObject> map; //вектор тайлов карты
    std::vector<MapObject> objects; //вектор персонажей, предметов карты

    std::string name;

    Unit(Level &level, string &fileName,
         string &name, float x, float y, float w, float h);

    // для проверки столкновений
    FloatRect getRect() { return {x, y, w, h}; }

    virtual void update(float time);

    virtual void checkCollision(int num);

    void acceptDamage(Unit from);

    void makeDamage(Unit to);
};