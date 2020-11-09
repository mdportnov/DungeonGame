#ifndef _POTION_H
#define _POTION_H

#include "include/model/Item.h"
#include "vector"
#include "string"

class Potion {
public:
    vector<pair<std::string, int>> changesList;

    void changeCharacteristics();
};

#endif //_POTION_H