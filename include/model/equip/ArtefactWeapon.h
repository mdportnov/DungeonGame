#pragma once

#include "vector"
#include "utility"
#include "string"
#include "Weapon.h"

using namespace std;

class ArtefactWeapon : public Weapon {
public:

    vector<pair<string, float>> changesListA();
};