#ifndef _CHEST_H
#define _CHEST_H

#include <include/model/Player.h>
#include "include/model/ObjectOnField.h"
#include "include/model/Item.h"
#include "include/model/equip/BunchOfKeys.h"
#include "vector"
#include "string"

using namespace std;

/**
 * Класс сундука, в котором хранится один предмет
 */
class Chest : public ObjectOnField {
public:
    bool isLocked;
    int lockLevel;

    Chest(Level &level, string &fileName, string &name, float x, float y, float w, float h, int layer, int lockLevel,
          bool isLocked);

    FloatRect getAreaRect();

    /**
     * Установка хранимого предмета
     */
    void setItem(Item *item);

    /**
    * Совершение попытки открыть в зависимости от характеристик игрока
    */
    bool open(Player &player);
private:
    /**
     * Получение ответа, можем ли открыть сундук или нет в зависимости от вероятности
     * @param prob вероятность
     */
    bool canOpen(double prob);

    /**
     * Получение вероятности открывания сундука в зависимости от характеристик игрока
     */
    float getProbabilityOfOpen(Player &player);

    Item *storedItem;
};

#endif //_CHEST_H