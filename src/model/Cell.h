#include "vector"
#include "utility"
#include "string"
#include "ObjectOnField.h"

using namespace std;

#ifndef _CELL_H
#define _CELL_H

class Cell {
public:
    int x;
    int y;
    ObjectOnField *pointerOnSmth;
    int cellType;
};

#endif //_CELL_H