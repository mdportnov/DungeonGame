#pragma once

#include <include/model/Item.h>

/**
 * Класс оружия
 */

class Weapon : public Item {
public:
    Weapon(Level &level, string &fileName, string &name, string &type, string &subType,
           float x, float y, float w, float h, int layer, int state, float damage);

    /**
    * Вычисляет урон
    */
    float calculateDamage() const;

    void draw(RenderWindow &window) override;

    virtual ~Weapon();

private:
    float damage;
};