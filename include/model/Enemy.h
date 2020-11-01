#include "Unit.h"

using namespace sf;

class Enemy : public Unit {
public:
    Enemy(const String &fileName, float x, float y, float w, float h) : Unit(fileName, x, y, w, h) {

    }
};