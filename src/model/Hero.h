#ifndef _HERO_H
#define _HERO_H

#include "Unit.h"
#include "TableOfCharacteristics.h"
#include "Weapon.h"
#include "Equipment.h"
#include "Potion.h"


class Hero: public Unit {
public: 
  TableOfCharacteristics attributes;
  Weapon weapon;
  Equipment equipment;
  int fullDamage;
  int maxQuantityOfPotions;
  vector<Item> inventory;
  
/**
 * @param item
 */
void takeItem(Item item);
  
/**
 * @param potion
 */
void drinkPotion(Potion potion);
  
void openChest();
  
/**
 * @param shortname
 */
void improveCharacteristicByXP(string shortname);
  
void kickEgorov();
private: 
  
int calculateDamage();
  
int calculateProtection();
  
bool updateWearings();
};

#endif //_HERO_H