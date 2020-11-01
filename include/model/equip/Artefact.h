#include "vector"
#include "utility"
#include "string"
using namespace std;

#ifndef _ARTEFACT_H
#define _ARTEFACT_H

class Artefact {
public:
    vector<std::string, int> getChangesList();

private:
    vector<pair<string, int>> changesList;
};

#endif //_ARTEFACT_H