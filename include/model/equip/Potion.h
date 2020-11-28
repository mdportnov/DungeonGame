#ifndef _POTION_H
#define _POTION_H

#include "include/model/Item.h"
#include "vector"
#include "string"
#include "ChangesAttributes.h"

class Potion : public Item, public ChangesAttributes {
public:
    int timer = 10;
    bool isUsingNow = false;

    Potion(Level &level, string &fileName, string &name,
           string &type, string &subType, float x, float y, float w, float h, int layer, int state,
           const map<string, string> &changesList);
};

#endif