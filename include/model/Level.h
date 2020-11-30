#pragma once
#include "../main.h"

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <include/TinyXML/tinyxml.h>
#include "MapObject.h"
#include "Layer.h"

using namespace std;

/**
 * Класс, характеризующих загруженный уровень
 */
class Level {
public:
    int currentLayer;

    /**
     * Загрузка карты: тайлы, объекты (лестницы, стены)
     */
    bool loadStaticMapFromFile(const string &filename);

    /**
     * Загрузка характеристик объектов на уровне
     */
    bool loadDynamicObjectsFromFile(const string &filename);

    /**
     * Получить статические объекты текущего слоя уровня
     */
    vector<MapObject> getAllStaticObjects();

    /**
     * Получить динамические объекты текущего слоя уровня
     */
    vector<MapObject> getAllDynamicObjects();
    /**
     * Отрисовка уровня
     */
    void draw(sf::RenderWindow &window);

    /**
     * Поднимемся наверх!
     */
    void goUp();

    /**
     * Опустимся вниз!
     */
    void goDown();
    /**
     * Получение объекта игрока
     */
    MapObject getPlayer();

    /**
     * Получение объектов по их типу
     */
    vector<MapObject> getObjectsByType(const string &type);

private:
    int countOfLayers;
    float width, height, tileWidth, tileHeight, objectsTileWidth, objectsTileHeight;
    int firstTileID;
    sf::Texture tileSetImage;
    sf::Texture itemsTileSetImage;

    vector<std::vector<MapObject>> staticObjects; // стены, лестницы (object из objectgroup) из level.tmx

    vector<std::vector<MapObject>> dynamicObjects; // предметы, юниты

    vector<Layer> layers; // layers из level.tmx
};
