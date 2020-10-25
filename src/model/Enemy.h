#ifndef _ENEMY_H
#define _ENEMY_H

#include "Unit.h"
#include "string"

using namespace std;

class Enemy : public Unit {
public:
    bool state;
    bool isAlive;
    string type;

    void pursueHero();

    void kickStudent();
};

#endif //_ENEMY_H