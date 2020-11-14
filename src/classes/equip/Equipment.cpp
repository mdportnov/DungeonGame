#include "include/model/equip/Equipment.h"

Equipment::Equipment(Level &level, string &fileName, string &name, string &type, string &subType, float x, float y,
                     float w, float h, int state, float protection, int eqType, int materialType) : Item(
        level, fileName, name, type, subType, x, y, w, h, state) {
    this->protection = protection;
    this->eqType = eqType;
    this->materialType = materialType;
}
