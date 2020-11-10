#include "include/main.h"
#include "Level.h"
#include "ObjectOnField.h"

#pragma once

using namespace sf;

class Unit : public ObjectOnField {
public:
    float dx, dy, speed, health;
    int framesCount = 0;
    double currentFrame = 0;
    Image image;
    bool isAlive;
    std::vector<Object> map; //вектор тайлов карты
    std::vector<Object> objects; //вектор персонажей, предметов карты

    std::string name;

    Unit(Level &level, std::string &fileName,
         std::string &name, float x, float y, float w, float h);

    // для проверки столкновений
    FloatRect getRect() { return {x, y, w, h}; }

    virtual void update(float time);

    virtual void checkCollision(int num);

    void acceptDamage(Unit from);

    void makeDamage(Unit to);
};