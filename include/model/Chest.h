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

    Chest(Level &level, string &fileName, string &name, float x, float y, float w, float h, int lockLevel, bool isLocked);

    FloatRect getAreaRect();

    void setItem(Item item);

    Item getItem();

    bool open(Player &player);

    pair<int, int> getInfo();

private:
//    Item storedItem;

    int getProbabilityOfOpen(Player hero);

    int getProbabilityOfBroken(Player hero);
};

#endif //_CHEST_H