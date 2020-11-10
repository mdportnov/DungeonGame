#include "include/model/Item.h"

Item::Item(Level level, string &fileName, string &name,
           float x, float y, float w, float h) : ObjectOnField(x, y, w, h, level) {
    this->name = name;
    this->filename = fileName;
}

