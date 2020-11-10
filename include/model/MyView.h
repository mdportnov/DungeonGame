#pragma once

#include "include/main.h"
using namespace sf;

class MyView {
private:
public:
    sf::View view;

    void getPlayerCoordinateForView(float x, float y);

    void viewMap(float time);

    void changeView();
};