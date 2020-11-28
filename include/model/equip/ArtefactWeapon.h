#pragma once

#include "vector"
#include "utility"
#include "string"
#include "Weapon.h"
#include "ChangesAttributes.h"

using namespace std;

class ArtefactWeapon : virtual public Weapon, public ChangesAttributes{
public:
    ArtefactWeapon(Level &level, string &fileName, string &name, string &type, string &subType, float x, float y,
                   float w, float h, int layer, int state, float damage, const map<string, string> &changesList);

    void draw(RenderWindow &window);
//    vector<pair<string, float>> changesListA;
};