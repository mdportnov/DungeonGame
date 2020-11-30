#include "HashMap.h"
#include "string"

#pragma once
using namespace std;

int main() {
    HashMap<string, float> h;

    h.insert("mxhp", 20);
    h.insert("xp", 20);
    h.insert("sp", 0.01);
    h.insert("pw", 3);
    h.insert("dx", 0.05);
    h.insert("st", 0.05);

    h["hp"] = 100.0;

    for (auto & it : h) {
        it.print();
    }

    return 0;
}
