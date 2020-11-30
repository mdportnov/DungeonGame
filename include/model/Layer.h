#pragma once

#include "iostream"
#include "include/main.h"

/**
 * Класс слоя тайлов
 */
class Layer {
public:
    int opacity{};
    std::vector<sf::Sprite> tiles;
    Layer layer();
};

