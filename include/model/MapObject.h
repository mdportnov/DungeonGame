#pragma once

#include "iostream"
#include "include/main.h"

using namespace std;

/**
 * Util-класс для десериализации данных из XML
 */
class MapObject {
public:
    string name;
    string type;
    string subType;
    int layer;
    sf::Rect<float> rect;
    map<string, string> properties;

    sf::Sprite sprite;
    string imagePath;
};