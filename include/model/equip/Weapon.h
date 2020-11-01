#ifndef _WEAPON_H
#define _WEAPON_H

#include "EnchantedWeapon.h"
#include "Artefact.h"
#include "src/model/Item.h"


class Weapon: public EnchantedWeapon, public Artefact, public Item {
public: 
  string name;
  
void getDamage();
  
void setDamage();
private: 
  int damage;
  
void calculateDamage();
};

#endif //_WEAPON_H