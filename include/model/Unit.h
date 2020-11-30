#pragma once

#include <include/model/equip/Weapon.h>
#include <src/HashMap.h>
#include "include/main.h"
#include "Level.h"
#include "ObjectOnField.h"
#include "MapObject.h"

using namespace sf;
using namespace std;

/**
 * Класс персонажа, имеющий определенные характеристики
 */
class Unit : public ObjectOnField {
public:
//    std::map<string, float> attributes;
    HashMap<string, float> attributes;
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

    /**
     * Проверка столкновения персонажа по оси
     */
    virtual void checkCollision(int axis);

    /**
     * Получение урона от другого персонажа
     */
    virtual void acceptDamageFrom(Unit *unit);

    virtual void draw(RenderWindow &window);

    /**
     * Вычисление наносимого урона с учётом носимого инвентаря
     */
    virtual float calculateDamage(Unit *unit);
};