#ifndef _CHEST_H
#define _CHEST_H

#include <include/model/Player.h>
#include "include/model/ObjectOnField.h"
#include "include/model/Item.h"
#include "include/model/equip/BunchOfKeys.h"
#include "vector"
#include "string"

using namespace std;

class Chest : public ObjectOnField {
public:
    bool isLocked;
    int lockLevel;

    Chest(Level &level, string &fileName, string &name, float x, float y, float w, float h, int layer, int lockLevel,
          bool isLocked);

    FloatRect getAreaRect();

    void setItem(Item *item);

    bool open(Player &player);

    bool canOpen(double prob);
private:
    Item *storedItem;

    float getProbabilityOfOpen(Player &player);
};

#endif //_CHEST_H