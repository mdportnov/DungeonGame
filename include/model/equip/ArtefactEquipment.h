#include "vector"
#include "utility"
#include "string"
using namespace std;


#ifndef _ARTEFACTEQUIPMENT_H
#define _ARTEFACTEQUIPMENT_H

#include "Artefact.h"
#include "Equipment.h"


class ArtefactEquipment: public Artefact, public Equipment {
public:

    ArtefactEquipment() {}
};

#endif //_ARTEFACTEQUIPMENT_H