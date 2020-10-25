#ifndef _UNIT_H
#define _UNIT_H

#include "ObjectOnField.h"

class Unit: public ObjectOnField {
public: 
  int x;
  int y;
  
/**
 * @param from
 */
void acceptDamage(Unit from);
  
/**
 * @param to
 */
void makeDamage(Unit to);
  
/**
 * @param x
 * @param y
 */
void step(int x, int y);
};

#endif //_UNIT_H