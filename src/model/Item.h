#ifndef _ITEM_H
#define _ITEM_H

#include "EnchantedWeapon.h"
#include "Artefact.h"
#include "ObjectOnField.h"


class Item: public EnchantedWeapon, public Artefact, public ObjectOnField {
public: 
  string name;
};

#endif //_ITEM_H