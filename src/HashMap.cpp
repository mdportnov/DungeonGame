#include "HashMap.h"
#include "string"

#pragma once
using namespace std;

int main() {
    HashMap<string, float> h;
    h.push("sp", 20);
    h.push("dx", 0.1);
    h.push("hp", 100);
    h.push("pw", 10);
    h.push("hp", 1000);
    h.push("hp", 10000);
    h.print();
    cout<<h.get("hp")<<endl;
    cout<<h.get("st");

    return 0;
}
