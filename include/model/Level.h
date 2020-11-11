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

class Level {
public:
    bool loadMapFromFile(const string &filename);

    bool loadStateFromFile(const string &filename);

    MapObject getObject(string name);

    vector<MapObject> getObjectsByName(string name);

    vector<MapObject> getAllMapObjects();

    void draw(sf::RenderWindow &window);

    sf::Vector2i getTileSize() const;

    void goUp();

    void goDown();

    int currentTileLayer = 0, currentObjectsLayer = 0;

    vector<MapObject> getEnemies();

    MapObject getPlayer();

    vector<MapObject> getObjectsByType(const string &type);

    vector<MapObject> getItems();

    vector<MapObject> getAllDynamicObjects();

    void deleteObject(vector<MapObject>::const_iterator it);

    vector<MapObject> getDoors();

    vector<MapObject> getChests();

private:
    int countOfLayers;
    float width, height, tileWidth, tileHeight, objectsTileWidth, objectsTileHeight;
    int firstTileID;
    sf::Rect<float> drawingBounds;
    sf::Texture tileSetImage;
    sf::Texture itemsTileSetImage;

    vector<std::vector<MapObject>> staticObjects; // стены, лестницы (object из objectgroup) из level.tmx

    vector<std::vector<MapObject>> dynamicObjects; // предметы, юниты

    vector<Layer> layers; // layers из level.tmx
};
