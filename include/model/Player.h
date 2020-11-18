#pragma once

#include <include/model/equip/BunchOfKeys.h>
#include "include/model/equip/Weapon.h"
#include "include/model/equip/Equipment.h"
#include "include/model/equip/Potion.h"
#include "Unit.h"
#include "MyView.h"
#include "Level.h"
#include "Door.h"
#include "list"

using namespace sf;

class Player : public Unit {
public:
    Equipment *equipment[3] = {nullptr, nullptr, nullptr}; // helmet, breastplate, boots
    std::vector<Potion *> potions;
    Weapon *weapon = nullptr;
    int currPotion = 0;
    int playerLevel;
//    TableOfCharacteristics attributes; потом реализовать мапу самому
    std::map<string, float> attributes;
    std::map<string, float> attributesDiff;
    BunchOfKeys bunchOfKeys;
    MyView *view;

    enum class STATE {
        stay, onladderup, onladderdown
    };

    STATE STATE = STATE::stay;

    std::map<std::string, bool> key;

    Player(Level &level, MyView &view, string fileName, string name, float x, float y, float w, float h, int layer,
           std::map<string, string> map);

    void update(float time) override;

    void keyboard();

    void control(float time);

    void checkCollision(int num) override;

    void takeItem(Item *&item);

    vector<pair<string, float>> drinkPotion();

    void acceptDamageFrom(Unit *unit) override;

    float calculateProtection();

    void draw(RenderWindow &window) override;

    float getSkillValue(const string &shortname);

    void changeSkillValue(const string &shortname, float diff);

    bool isHit(double prob);

    void deletePotion();

    float calculateDamage(Unit *unit) override;
};