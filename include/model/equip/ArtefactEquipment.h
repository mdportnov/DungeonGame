#pragma once

#include "vector"
#include "utility"
#include "string"

using namespace std;

#include "Equipment.h"

class ArtefactEquipment : public Equipment {
public:
    vector<pair<string, float>> changesListA;
    map<string, string> changesMapFromXML;

    ArtefactEquipment(Level &level, string &fileName, string &name, string &type, string &subType, float x, float y,
                      float w, float h, int state, float protection, int eqType, int materialType,
                      map<string, string> properties);

    void draw(RenderWindow &window) override;

};
