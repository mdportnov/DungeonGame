#pragma once

#include "vector"
#include "utility"
#include "string"

using namespace std;

#include "Equipment.h"

class ArtefactEquipment : public Equipme#pragma oncent {
public:
    vector<pair<string, float>> changesListA;

    ArtefactEquipment(Level &level, string &fileName, string &name, string &type, string &subType, float x, float y,
                      float w, float h, int state, float protection, int eqType, int materialType,
                      const vector<pair<string, float>> &changesListA);
};
