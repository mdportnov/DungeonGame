#include "vector"
#include "utility"
#include "string"

using namespace std;

#ifndef _BUNCHOFKEYS_H
#define _BUNCHOFKEYS_H

#include "Item.h"


class BunchOfKeys : public Item {
public:
    string name;

    void brokeKey();

    void addNewOne();

private:
    int quantity;
};

#endif //_BUNCHOFKEYS_H