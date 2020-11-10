#ifndef DUNGEONGAME_DOOR_H
#define DUNGEONGAME_DOOR_H


#include <include/model/ObjectOnField.h>

class Door : public ObjectOnField {
public:
    bool isLocked = true;

    Door(Level &level, string &fileName, string &name, float x, float y, float w, float h);

    void update(float time);
};


#endif //DUNGEONGAME_DOOR_H
