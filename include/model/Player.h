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

/**
  *  Класс игрока
  */
class Player : public Unit {
public:
    Equipment *equipment[3] = {nullptr, nullptr, nullptr}; // helmet, breastplate, boots
    std::vector<Potion *> potions;
    Weapon *weapon = nullptr;
    int currPotion = 0;
    int playerLevel = 0;
    HashMap<string, float> attributesDiff;
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

    /**
     * Изменение ускорения игрока по нажатой клавише
     */
    void keyboard();

    /**
    * Отрисовка текстуры игрока
    */
    void control(float time);

    void checkCollision(int num) override;

    /**
     * Поднять предмет и сложить его в соответствующий его типу слот
     */
    void takeItem(Item *&item);

    /**
     * Получить характеристики, меняемые зельем
     */
    vector<pair<string, float>> drinkPotion();

    void acceptDamageFrom(Unit *unit) override;

    /**
     * Вычислить параметр защиты в зависимости от экипировки
     */
    float calculateProtection();

    void draw(RenderWindow &window) override;

    /**
     * Получить значение характеристики персонажа
     */
    float getSkillValue(const string &shortname);
    /**
     * Изменить значение характеристики персонажа
     */
    void changeSkillValue(const string &shortname, float diff);

    /**
     * Попадание или пропах при ударе в зависимости от ловкости
     */
    bool isHit(double prob);

    /**
     * Выкинуть зелье
     */
    void deletePotion();

    float calculateDamage(Unit *unit) override;
};