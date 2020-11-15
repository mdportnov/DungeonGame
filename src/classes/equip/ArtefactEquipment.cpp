#include "include/model/equip/ArtefactEquipment.h"

ArtefactEquipment::ArtefactEquipment(Level &level, string &fileName, string &name, string &type, string &subType,
                                     float x, float y, float w, float h, int state, float protection, int eqType,
                                     int materialType, const vector<pair<string, float>> &changesListA) : Equipment(
        level, fileName, name, type, subType, x, y, w, h, state, protection, eqType, materialType), changesListA(
        changesListA) {}
