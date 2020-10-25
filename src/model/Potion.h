#ifndef _POTION_H
#define _POTION_H

#include "Item.h"
#include "vector"
#include "utility"

using namespace std;

class Potion : public Item {
public:
    vector<pair<string, int>> changesList;

    void changeCharacteristics();
};

#endif //_POTION_H