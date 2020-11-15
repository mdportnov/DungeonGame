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

    int getSize();

private:
    int size = 0;
    int maxSize = 5;
};

#endif //_BUNCHOFKEYS_H