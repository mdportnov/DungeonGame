#ifndef _GAME_H
#define _GAME_H

#include "string"
#include "Map.h"

using namespace std;

class Game {
public:

/**
 * @param file
 */
    map loadLevelFromFile(string file);

    void saveCurrentProgress();

    void startNewGame();

    void loadFromLastCheckPoint();
};

#endif //_GAME_H