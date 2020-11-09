#ifndef _ITEM_H
#define _ITEM_H

#include "include/model/ObjectOnField.h"
#include "Level.h"

class Item : public ObjectOnField {
public:
    string name, filename;

    Item(Level level, std::string &fileName, std::string &name, float x, float y, float w, float h) : ObjectOnField(x,
                                                                                                                    y,
                                                                                                                    w,
                                                                                                                    h,
                                                                                                                    level) {
        this->name = name;
        this->filename = filename;
    }
//        this->image.loadFromFile("../res/img/" + fileName);

};

#endif //_ITEM_H