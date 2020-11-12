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
    Weapon *weapon = nullptr; // удалять меньший по урону с карты
    float dx, dy, speed;
    float health, defaultDamage=5;
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

    virtual void acceptDamageFrom(Unit &unit);

    float calculateDamage();

    void makeDamage(Unit to);
};