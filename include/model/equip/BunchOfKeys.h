#include "vector"
#include "utility"
#include "string"

using namespace std;

#ifndef _BUNCHOFKEYS_H
#define _BUNCHOFKEYS_H

#include "include/model/Item.h"


class BunchOfKeys {
public:
    void brokeKey();

    void addNewOne();

private:
    int size;
    string name;
    int maxSize = 5;
};

#endif //_BUNCHOFKEYS_H