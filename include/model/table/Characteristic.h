#include "vector"
#include "utility"
#include "string"

using namespace std;

#ifndef _CHARACTERISTIC_H
#define _CHARACTERISTIC_H

enum Characteristics { health, maxHealth, precision, power, stamina, levelPoints };

class Characteristic {
public:
    string name;
    string shortname;
    int value;
};

#endif //_CHARACTERISTIC_H