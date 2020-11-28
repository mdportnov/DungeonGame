#ifndef DUNGEONGAME_CHANGESATTRIBUTES_H
#define DUNGEONGAME_CHANGESATTRIBUTES_H

#include "iostream"
#include "utility"
#include "vector"
#include "map"

using namespace std;

class ChangesAttributes {
public:
    vector<pair<string, float>> changesListA;

    ChangesAttributes(const map<string, string> &properties);
};

#endif
