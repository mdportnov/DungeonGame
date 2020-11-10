#pragma once

#include "iostream"
#include "include/main.h"

class Layer {
public:
    int opacity{};
    std::vector<sf::Sprite> tiles;
    Layer layer();
};

