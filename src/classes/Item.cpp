#include "include/model/Item.h"

Item::Item(Level &level, string &fileName, string &name, string &type, string &subType,
           float x, float y, float w, float h, int state) : ObjectOnField(level, fileName, name, x, y, w, h) {
    this->subType = subType;
    this->type = type;
    this->state = static_cast<STATE>(state);
}