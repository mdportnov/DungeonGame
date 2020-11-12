#pragma once

#include <include/model/equip/BunchOfKeys.h>
#include "include/model/equip/Weapon.h"
#include "include/model/equip/Equipment.h"
#include "include/model/equip/Potion.h"
#include "include/model/table/TableOfCharacteristics.h"
#include "Unit.h"
#include "list"
#include "MyView.h"
#include "Level.h"

class Level;

using namespace sf;

class Player : public Unit {
private:
    int defaultDamage = 10;
public:
    Weapon *weapon = nullptr; // удалять меньший по урону с карты
    Equipment *equipment[3]{}; // helmet, breastplate, boots
    int maxQuantityOfPotions{};

    TableOfCharacteristics attributes;
    BunchOfKeys bunchOfKeys;
    MyView *view;

    enum class STATE {
        stay, onladderup, onladderdown, walk
    };

    STATE STATE = STATE::stay;

    std::map<std::string, bool> key;

    Player(Level &level, MyView &view, std::string fileName, std::string name,
           float x, float y, float w, float h);

//    Player(Level level, sf::Sprite &sprite, std::string name,
//           float x, float y, float w, float h) : Unit(level, sprite, name, x, y, w, h) {
//        this->sprite = sprite;
//        framesCount = 5;
//    }

    void update(float time) override;

    void keyboard();

    void control(float time);

    void checkCollision(int num) override;

    void takeItem(Item *item);

    void drinkPotion(const Potion *potion);

    void openChest();

    void improveCharacteristicByXP(string shortname);

    void kickEgorov();

    int calculateDamage();

    int calculateProtection();

    bool updateWearings();
};