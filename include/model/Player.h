#include <include/model/equip/Weapon.h>
#include <include/model/equip/Equipment.h>
#include <include/model/equip/Potion.h>
#include <include/model/table/TableOfCharacteristics.h>
#include "Unit.h"
#include "list"

#pragma once

using namespace sf;

class Player : public Unit {
public:
    Weapon weapon;
//    Equipment equipment[3] // helmet, breastplate, boots
    int fullDamage;
    int maxQuantityOfPotions;
    vector<Item> inventory;
    TableOfCharacteristics attributes;
    std::vector<Object> objects; //вектор персонажей, предметов карты

    enum {
        stay, onladderup, onladderdown, walk
    } STATE;

    std::map<std::string, bool> key;

    Player(Level level, std::string fileName, std::string name,
           float x, float y, float w, float h) : Unit(level, fileName, name, x, y, w, h) {
        framesCount = 5;
        objects = level.getAllObjects();
    }

    Player(Level level, sf::Sprite &sprite, std::string name,
           float x, float y, float w, float h) : Unit(level, sprite, name, x, y, w, h) {
        this->sprite = sprite;
        framesCount = 5;
    }

    void update(float time) override {
        control(time);
        keyboard();
        Unit::update(time);
    }

    void keyboard() {
        if (key["A"]) {
            dx = -speed;
            dy = 0;
            if (STATE == stay) STATE = walk;
        }

        if (key["D"]) {
            dx = speed;
            dy = 0;
            if (STATE == stay) STATE = walk;
        }

        if (key["W"]) {
            dx = 0;
            dy = -speed;
        }

        if (key["S"]) {
            dx = 0;
            dy = speed;
        }

        /////////////////////если клавиша отпущена///////////////////////////
        if (!(key["D"] || key["A"])) {
            dx = 0;
            if (STATE == walk) STATE = stay;
        }

        if (!(key["W"] || key["S"])) {
            dy = 0;
            if (STATE == walk) STATE = stay;
        }

        key["A"] = key["S"] = key["W"] = key["D"] = key["Space"] = false;
    }

    void control(float time) {
        if (key["A"]) {
            sprite.setOrigin({30, 0});
            sprite.setScale({-1, 1});
            speed = 0.1;

            currentFrame += 0.005 * time;
            if (currentFrame > framesCount) currentFrame -= framesCount;
            sprite.setTextureRect(IntRect(30 * int(currentFrame), 0, 30, 50));
            getPlayerCoordinateForView(this->getX(), this->getY());
        }

        if (key["D"]) {
            sprite.setScale({1, 1});
            sprite.setOrigin({0, 0});
            speed = 0.1;

            currentFrame += 0.005 * time;
            if (currentFrame > framesCount) currentFrame -= framesCount;
            sprite.setTextureRect(IntRect(30 * int(currentFrame), 0, 30, 50));
            getPlayerCoordinateForView(this->getX(), this->getY());
        }

        if (key["W"]) {
            speed = 0.1;
            currentFrame += 0.005 * time;
            if (currentFrame > framesCount) currentFrame -= framesCount;
            sprite.setTextureRect(IntRect(30 * int(currentFrame), 0, 30, 50));
            getPlayerCoordinateForView(this->getX(), this->getY());
        }

        if (key["S"]) {
            speed = 0.1;
            currentFrame += 0.005 * time;
            if (currentFrame > framesCount) currentFrame -= framesCount;
            sprite.setTextureRect(IntRect(30 * int(currentFrame), 0, 30, 50));
            getPlayerCoordinateForView(this->getX(), this->getY());
        }
    }

    void checkCollision(int num) override {
        Unit::checkCollision(num);
        for (auto &i : map)
            if (getRect().intersects(i.rect)) {
                if (i.name == "ladder_up" &&
                    Mouse::isButtonPressed(sf::Mouse::Left)
                        ) {
                    STATE = onladderup;
                }
                if (i.name == "ladder_down" &&
                    Mouse::isButtonPressed(sf::Mouse::Left)
                        ) {
                    STATE = onladderdown;
                }
            }

//        for (it = objects.begin(); it != objects.end(); ++it)
//            if (getRect().intersects(it->rect)) {
//                if (it->name == "python") {
//                    level.deleteObject(it);
//                    objects=level.getAllObjects();
//                }
//            }
    }

    void takeItem(Item item) {

    };

    void drinkPotion(Potion potion) {

    };

    void openChest() {};

    void improveCharacteristicByXP(string shortname) {};

    void kickEgorov() {};

    int calculateDamage() {};

    int calculateProtection() {};

    bool updateWearings() {};
};