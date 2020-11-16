#pragma once

#include "iostream"
#include "include/main.h"

using namespace std;

class MapObject {
public:
    string name;
    string type;
    string subType;
    sf::Rect<float> rect;
    map<string, string> properties;

    sf::Sprite sprite;
    string imagePath;
};