#include "vector"
#include "utility"
#include "string"
using namespace std;

#ifndef _ARTEFACTWEAPON_H
#define _ARTEFACTWEAPON_H

#include "Artefact.h"
#include "Weapon.h"


class ArtefactWeapon: public Artefact, public Weapon {
public:

vector<pair<string, int>> changesListA();
};

#endif //_ARTEFACTWEAPON_H