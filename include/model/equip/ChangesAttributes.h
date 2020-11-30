#ifndef DUNGEONGAME_CHANGESATTRIBUTES_H
#define DUNGEONGAME_CHANGESATTRIBUTES_H

#include "iostream"
#include "utility"
#include "vector"
#include "map"
#include "list"

using namespace std;

/*
 *
 *
 *
 * */


class ChangesAttributes {
    vector<string> asdasd{
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
