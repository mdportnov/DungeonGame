#ifndef _POTION_H
#define _POTION_H

#include "include/model/Item.h"
#include "vector"
#include "string"

class Potion : public Item {
public:
    vector<pair<string, float>> changesList;
    int timer;

    Potion(Level &level, string &fileName, string &name, string &type, string &subType, float x, float y,
           float w,
           float h, int state, const vector<pair<string, float>> &changesList);
};

#endif