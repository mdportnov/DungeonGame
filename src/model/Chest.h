#ifndef _CHEST_H
#define _CHEST_H

#include "include/model/ObjectOnField.h"
#include "include/model/Item.h"
#include "BunchOfKeys.h"
#include "Hero.h"
#include "vector"
#include "utility"
#include "string"

using namespace std;

class Chest : public ObjectOnField {
public:

/**
 * @param item
 */
    void setItem(Item item);

    Item getItem();

/**
 * @param key
 */
    bool open(BunchOfKeys key);

    void setLockLevel();

    void getLockLevel();

    pair<int, int> getInfo();

private:
    Item storedItem;
    int lockLevel;

/**
 * @param hero
 */
    int getProbabilityOfOpen(Hero hero);

/**
 * @param hero
 */
    int getProbabilityOfBroken(Hero hero);
};

#endif //_CHEST_H