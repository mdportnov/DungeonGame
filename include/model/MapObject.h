#pragma once

#include "iostream"
#include "include/main.h"

using namespace std;

class MapObject {
public:
    int getPropertyInt(string name);

    float getPropertyFloat(string name);

    string getPropertyString(string name);

    string name;
    string type;
    sf::Rect<float> rect;
    map<std::string, std::string> properties;

    sf::Sprite sprite;
    string imagePath;
};