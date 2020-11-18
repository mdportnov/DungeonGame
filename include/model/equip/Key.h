#ifndef DUNGEONGAME_KEY_H
#define DUNGEONGAME_KEY_H


#include <include/model/Item.h>

class Key : public Item {
public:
    Key(Level &level, string &fileName, string &name, string &type, string &subType, float x, float y, float w,
        float h, int layer, int state);
};


#endif
