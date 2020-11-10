#include "include/model/Item.h"

Item::Item(Level &level, string &fileName, string &name,
           float x, float y, float w, float h) : ObjectOnField(level, x, y, w, h) {
    this->name = name;
    this->filename = fileName;
}

