#ifndef _LEVEL_H
#define _LEVEL_H

#include "iostream"
#include <stdio.h>
#include "Cell.h"

class Level {
public:
    int width;
    int height;
//    File map;
    int currX;
    int currY;
    vector<vector<Cell>> cells;

    void setMapSize(int w, int h);

    tuple<int, int> getMapSize();

    string getCellType(int x, int y);

    void setCellType(int x, int y, int type);

    void changeDoorState(int x, int y);

    void getXML();
};

#endif //_LEVEL_H