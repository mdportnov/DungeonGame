#include <include/model/equip/Weapon.h>
#include <include/model/equip/Equipment.h>
#include <include/model/equip/Potion.h>
#include <include/model/table/TableOfCharacteristics.h>
#include "Unit.h"

#pragma once

using namespace sf;

class Player : public Unit {
public:
    Weapon weapon;
    Equipment equipment[3]; // helmet, breastplate, boots
    int fullDamage;
    int maxQuantityOfPotions;
    vector<Item> inventory;
    TableOfCharacteristics attributes;

    sf::SoundBuffer buffer;

    sf::Sound sound;

    Player(Level level, std::string fileName, std::string name,
           float x, float y, float w, float h) : Unit(level, fileName, name, x, y, w, h) {

        obj = level.getAllObjects();
        framesCount = 5;
        buffer.loadFromFile("../res/sound/hookah.wav");
        sound.setBuffer(buffer);
    }

    void update(float time) override {
        Unit::update(time);
        control(time);
    }

    void control(float time) {
        if (Keyboard::isKeyPressed(Keyboard::A)) {
            sprite.setOrigin({30, 0});
            sprite.setScale({-1, 1});
            state = left;
            speed = 0.1;
            currentFrame += 0.005 * time;
            if (currentFrame > framesCount) currentFrame -= framesCount;
            sprite.setTextureRect(IntRect(30 * int(currentFrame), 0, 30, 50));
            getPlayerCoordinateForView(this->getX(), this->getY());
        }

        if (Keyboard::isKeyPressed(Keyboard::D)) {
            sprite.setScale({1, 1});
            sprite.setOrigin({0, 0});
            state = right;
            speed = 0.1;
            currentFrame += 0.005 * time;
            if (currentFrame > framesCount) currentFrame -= framesCount;
            sprite.setTextureRect(IntRect(30 * int(currentFrame), 0, 30, 50));
            getPlayerCoordinateForView(this->getX(), this->getY());
        }

        if (Keyboard::isKeyPressed(Keyboard::W)) {
            state = up;
            speed = 0.1;
            currentFrame += 0.005 * time;
            if (currentFrame > framesCount) currentFrame -= framesCount;
            sprite.setTextureRect(IntRect(30 * int(currentFrame), 0, 30, 50));
            getPlayerCoordinateForView(this->getX(), this->getY());
        }

        if (Keyboard::isKeyPressed(Keyboard::S)) {
            state = down;
            speed = 0.1;
            currentFrame += 0.005 * time;
            if (currentFrame > framesCount) currentFrame -= framesCount;
            sprite.setTextureRect(IntRect(30 * int(currentFrame), 0, 30, 50));
            getPlayerCoordinateForView(this->getX(), this->getY());
        }

        if (Mouse::isButtonPressed(sf::Mouse::Left)) {
            takeItem(Item("name"));
        }
//        if (Keyboard::isKeyPressed(Keyboard::H)) {
//            sound.play();
//        }
    }

    void checkCollision(int num) override {
        Unit::checkCollision(num);
        for (auto &i : obj)
            if (getRect().intersects(i.rect)) {
                if (i.name == "ladder_up" &&
                    Mouse::isButtonPressed(sf::Mouse::Left)
                        ) {
                    state = onladderup;
                }
                if (i.name == "ladder_down" &&
                    Mouse::isButtonPressed(sf::Mouse::Left)
                        ) {
                    state = onladderdown;
                }
            }
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