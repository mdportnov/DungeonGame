#include <include/model/equip/Weapon.h>
#include <include/model/equip/Equipment.h>
#include <include/model/equip/Potion.h>
#include <include/model/table/TableOfCharacteristics.h>
#include "Unit.h"

using namespace sf;

class Player : public Unit {
public:
    Weapon weapon;
    Equipment equipment[3]; // helmet, breastplate, boots
    int fullDamage;
    int maxQuantityOfPotions;
    vector<Item> inventory;
    TableOfCharacteristics attributes;


    Player(const String &fileName, float x, float y, float w, float h) : Unit(fileName, x, y, w, h) {
        framesCount = 4;
    }

    void update(float time) override {
        Unit::update(time);
        control(time);
    }

    void control(float time) {
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            sprite.setScale(-1.f, 1.f);
            dir = 1;
            speed = 0.1;
            currentFrame += 0.005 * time;
            if (currentFrame > framesCount) currentFrame -= framesCount;
            sprite.setTextureRect(IntRect(30 * int(currentFrame), 0, 30, 50));
            getPlayerCoordinateForView(this->getX(), this->getY());
        }

        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            sprite.setScale(1.f, 1.f);
            dir = 0;
            speed = 0.1;
            currentFrame += 0.005 * time;
            if (currentFrame > framesCount) currentFrame -= framesCount;
            sprite.setTextureRect(IntRect(30 * int(currentFrame), 0, 30, 50));
            getPlayerCoordinateForView(this->getX(), this->getY());
        }

        if (Keyboard::isKeyPressed(Keyboard::Up)) {
            dir = 3;
            speed = 0.1;
            currentFrame += 0.005 * time;
            if (currentFrame > framesCount) currentFrame -= framesCount;
            sprite.setTextureRect(IntRect(30 * int(currentFrame), 0, 30, 50));
            getPlayerCoordinateForView(this->getX(), this->getY());
        }

        if (Keyboard::isKeyPressed(Keyboard::Down)) {
            dir = 2;
            speed = 0.1;
            currentFrame += 0.005 * time;
            if (currentFrame > framesCount) currentFrame -= framesCount;
            sprite.setTextureRect(IntRect(30 * int(currentFrame), 0, 30, 50));
            getPlayerCoordinateForView(this->getX(), this->getY());
        }
    }

    void takeItem(Item item){

    };

    void drinkPotion(Potion potion){

    };

    void openChest(){};

    void improveCharacteristicByXP(string shortname){};

    void kickEgorov(){};

    int calculateDamage(){};

    int calculateProtection(){};

    bool updateWearings(){};
};