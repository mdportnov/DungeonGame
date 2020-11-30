#ifndef DUNGEONGAME_CHANGESATTRIBUTES_H
#define DUNGEONGAME_CHANGESATTRIBUTES_H

#include "iostream"
#include "utility"
#include "vector"
#include "map"
#include "list"

using namespace std;

/**
 * Класс изменений, которые производят артефакты и зелья
 */

class ChangesAttributes {
    vector<string> existingChars{
            "sp",
            "st",
            "pw",
            "dx",
            "hp",
    };
public:
    vector<pair<string, float>> changesListA;

    ChangesAttributes(const map<string, string> &properties);
};

#endif
