#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <include/TinyXML/tinyxml.h>

#pragma once
using namespace std;

struct Layer {
    int opacity{};
    vector<sf::Sprite> tiles;
};

struct Object {
    int getPropertyInt(std::string name);

    float getPropertyFloat(std::string name);

    string getPropertyString(std::string name);

    string name;
    string type;
    sf::Rect<float> rect;
    map<std::string, std::string> properties;

    sf::Sprite sprite;
    std::string imagePath;
};

class Level {
public:
    bool loadMapFromFile(const std::string &filename);

    bool loadStateFromFile(const std::string &filename);

    Object getObject(std::string name);

    vector<Object> getObjectsByName(std::string name);

    vector<Object> getAllMapObjects();

    void draw(sf::RenderWindow &window);

    sf::Vector2i getTileSize() const;

    void goUp();

    void goDown();

    int currentTileLayer = 0, currentObjectsLayer = 0;

    vector<Object> getEnemies();

    Object getPlayer();

    vector<Object> getObjectsByType(const string &type);

    vector<Object> getItems();

    vector<Object> getAllObjects();

    void deleteObject(vector<Object>::const_iterator it);

private:
    int countOfLayers;
    float width, height, tileWidth, tileHeight, objectsTileWidth, objectsTileHeight;
    int firstTileID;
    sf::Rect<float> drawingBounds;
    sf::Texture tileSetImage;
    sf::Texture itemsTileSetImage;

    vector<std::vector<Object>> staticObjects; // стены, лестницы (object из objectgroup) из level.tmx

    vector<std::vector<Object>> dynamicObjects; // предметы, юниты

    vector<Layer> layers; // layers из level.tmx
};
