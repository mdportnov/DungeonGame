#ifndef _EQUIPMENT_H
#define _EQUIPMENT_H

#include "Item.h"
#include "Artefact.h"
#include "EnchantedWeapon.h"

class Equipment: public Item, public Artefact, public EnchantedWeapon {
public: 
  string type;
  int protection;
  string material;
};

#endif //_EQUIPMENT_H