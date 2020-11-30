#pragma once

#include "include/main.h"

using namespace sf;

/**
 * Класс камеры игрока
 */
class MyView {
private:
public:
    sf::View view;

    /**
     * Получение координат игрока для установки камеры
     */
    void getPlayerCoordinateForView(float x, float y);

    /**
     * Перемещение карты
     */
    void viewMap(float time);

    /**
     * Изменение положения камеры
     */
    void changeView();
};