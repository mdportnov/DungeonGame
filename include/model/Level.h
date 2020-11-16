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

    vector<MapObject> getAllStaticObjects();

    vector<MapObject> getAllDynamicObjects();

    void draw(sf::RenderWindow &window);

    void goUp();

    void goDown();

    int currentTileLayer = 0, currentObjectsLayer = 0;

    MapObject getPlayer();

    vector<MapObject> getObjectsByType(const string &type);

    void deleteObject(vector<MapObject>::const_iterator it);

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
