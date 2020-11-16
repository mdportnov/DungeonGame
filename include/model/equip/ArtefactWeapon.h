#pragma once

#include "vector"
#include "utility"
#include "string"
#include "Weapon.h"

using namespace std;

class ArtefactWeapon : public Weapon {
public:
    ArtefactWeapon(Level &level, string &fileName, string &name, string &type, string &subType, float x, float y,
                   float w, float h, int state, float damage, map<string, string> properties);

    map<string, string> changesMapFromXML;
    vector<pair<string, float>> changesListA;
};