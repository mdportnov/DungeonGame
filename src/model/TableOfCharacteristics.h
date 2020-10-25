#ifndef _TABLEOFCHARACTERISTICS_H
#define _TABLEOFCHARACTERISTICS_H

#include "Characteristic.h"
#include "Map.h"


class TableOfCharacteristics {
public: 
//  Iterator it;
  Characteristic chars[4];

  
/**
 * @param shortname
 */
Characteristic getCharacteristicByShortName(string shortname);
  
/**
 * @param shortname
 * @param diff
 */
void changeCharacteristicByShortName(string shortname, int diff);
  
int getCount();
private: 
  Map array;
};

#endif //_TABLEOFCHARACTERISTICS_H