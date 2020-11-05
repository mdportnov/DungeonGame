#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <include/TinyXML/tinyxml.h>

struct Layer {
    int opacity;
    std::vector<sf::Sprite> tiles;
};

struct Object {
    int getPropertyInt(std::string name);

    float getPropertyFloat(std::string name);

    std::string getPropertyString(std::string name);

    std::string name;
    std::string type;
    sf::Rect<float> rect;
    std::map<std::string, std::string> properties;

    sf::Sprite sprite;
};

class Level {
public:
    bool loadMapFromFile(const std::string &filename);

    bool loadStateFromFile(const std::string &filename);

    Object getObject(std::string name);

    std::vector<Object> getObjects(std::string name);

    std::vector<Object> getAllObjects();

    void draw(sf::RenderWindow &window);

    sf::Vector2i getTileSize() const;

    void goUp();

    void goDown();

    int getCountOfLayers() const;

    int currentTileLayer = 0, currentObjectsLayer = 0;

private:
    int countOfLayers;
    float width, height, tileWidth, tileHeight;
    int firstTileID;
    sf::Rect<float> drawingBounds;
    sf::Texture tileSetImage;
    std::vector<std::vector<Object>> objects; // стены, лестницы (object из objectgroup) из level.tmx
    std::vector<Layer> layers; // layers из level.tmx
};

int Object::getPropertyInt(std::string name) {
    return atoi(properties[name].c_str());
}

float Object::getPropertyFloat(std::string name) {
    return strtod(properties[name].c_str(), NULL);
}

std::string Object::getPropertyString(std::string name) {
    return properties[name];
}

// грузит ТОЛЬКО тайлы и объекты стен (solid) и лестниц(ladder_up/_down)
bool Level::loadMapFromFile(const std::string &filename) {
    TiXmlDocument levelFile(filename.c_str());

    // Загружаем XML-карту
    if (!levelFile.LoadFile()) {
        std::cout << "Loading level \"" << filename << "\" failed." << std::endl;
        return false;
    }

    // Работаем с контейнером map
    TiXmlElement *map;
    map = levelFile.FirstChildElement("map");

    // <map version="1.0" orientation="orthogonal"
    // width="10" height="10" tilewidth="50" tileheight="50">
    width = atoi(map->Attribute("width"));
    height = atoi(map->Attribute("height"));
    tileWidth = atoi(map->Attribute("tilewidth"));
    tileHeight = atoi(map->Attribute("tileheight"));

    // Берем описание тайлсета и идентификатор первого тайла
    TiXmlElement *tilesetElement;
    tilesetElement = map->FirstChildElement("tileset");
    firstTileID = atoi(tilesetElement->Attribute("firstgid"));

    // source - путь до картинки в контейнере image
    TiXmlElement *image;
    image = tilesetElement->FirstChildElement("image");
    std::string imagepath = image->Attribute("source");

    // ПУТЬ К ТАЙЛСЕТУ, загрузка
    sf::Image img;
    if (!img.loadFromFile("../res/" + imagepath)) {
        std::cout << "Failed to load tile sheet." << std::endl;
        return false;
    }

    img.createMaskFromColor(sf::Color(255, 255, 255));
    tileSetImage.loadFromImage(img);
    tileSetImage.setSmooth(true);

    // Получаем количество столбцов и строк тайлсета
    int columns = tileSetImage.getSize().x / tileWidth;
    int rows = tileSetImage.getSize().y / tileHeight;

    // Вектор из прямоугольников изображений (TextureRect)
    std::vector<sf::Rect<int> > subRects;

    for (int y = 0; y < rows; y++)
        for (int x = 0; x < columns; x++) {
            sf::Rect<int> rect;

            rect.top = y * tileHeight;
            rect.height = tileHeight;
            rect.left = x * tileWidth;
            rect.width = tileWidth;

            subRects.push_back(rect);
        }

    // Работа со слоями
    TiXmlElement *layerElement;
    layerElement = map->FirstChildElement("layer");
    while (layerElement) {
        Layer layer;

        // Если присутствует opacity, то задаем прозрачность слоя, иначе он полностью непрозрачен
        if (layerElement->Attribute("opacity") != nullptr) {
            float opacity = strtod(layerElement->Attribute("opacity"), nullptr);
            layer.opacity = 255 * opacity;
        } else {
            layer.opacity = 255;
        }

        // Контейнер <data>
        TiXmlElement *layerDataElement;
        layerDataElement = layerElement->FirstChildElement("data");

        if (layerDataElement == nullptr) {
            std::cout << "Bad map. No layer information found." << std::endl;
        }

        // Контейнер <tile> - описание тайлов каждого слоя
        TiXmlElement *tileElement;
        tileElement = layerDataElement->FirstChildElement("tile");

        if (tileElement == nullptr) {
            std::cout << "Bad map. No tile information found." << std::endl;
            return false;
        }

        float x = 0;
        float y = 0;

        while (tileElement) {
            int tileGID = atoi(tileElement->Attribute("gid"));
            int subRectToUse = tileGID - firstTileID;

            // Устанавливаем TextureRect каждого тайла
            if (subRectToUse >= 0) {
                sf::Sprite sprite;
                sprite.setTexture(tileSetImage);
                sprite.setTextureRect(subRects[subRectToUse]);
                sprite.setPosition(x * tileWidth, y * tileHeight);
                sprite.setColor(sf::Color(255, 255, 255, layer.opacity));

                layer.tiles.push_back(sprite);
            }

            tileElement = tileElement->NextSiblingElement("tile");

            x++;
            if (x >= width) {
                x = 0;
                y++;
                if (y >= height)
                    y = 0;
            }
        }

        layers.push_back(layer);

        layerElement = layerElement->NextSiblingElement("layer");
        countOfLayers++;
    }

    // Работа с объектами
    TiXmlElement *objectGroupElement;

    // Если есть слои объектов
    if (map->FirstChildElement("objectgroup") != nullptr) {
        objectGroupElement = map->FirstChildElement("objectgroup");
        while (objectGroupElement) {
            // Контейнер <object>
            TiXmlElement *objectElement;
            objectElement = objectGroupElement->FirstChildElement("object");

            std::vector<Object> currLayerObjects; // список объектов текущего слоя

            while (objectElement) {
                // Получаем все данные - тип, имя, позиция, etc
                std::string objectType;
                if (objectElement->Attribute("type") != nullptr) {
                    objectType = objectElement->Attribute("type");
                }
                std::string objectName;
                if (objectElement->Attribute("name") != nullptr) {
                    objectName = objectElement->Attribute("name");
                }
                int x = atoi(objectElement->Attribute("x"));
                int y = atoi(objectElement->Attribute("y"));

                int width, height;

                sf::Sprite sprite;
                sprite.setTexture(tileSetImage);
                sprite.setTextureRect(sf::Rect<int>(0, 0, 0, 0));
                sprite.setPosition(x, y);

                if (objectElement->Attribute("width") != nullptr) {
                    width = atoi(objectElement->Attribute("width"));
                    height = atoi(objectElement->Attribute("height"));
                } else {
                    width = subRects[atoi(objectElement->Attribute("gid")) - firstTileID].width;
                    height = subRects[atoi(objectElement->Attribute("gid")) - firstTileID].height;
                    sprite.setTextureRect(subRects[atoi(objectElement->Attribute("gid")) - firstTileID]);
                }

                // Экземпляр объекта
                Object object;
                object.name = objectName;
                object.type = objectType;
                object.sprite = sprite;

                sf::Rect<float> objectRect;
                objectRect.top = y;
                objectRect.left = x;
                objectRect.height = height;
                objectRect.width = width;
                object.rect = objectRect;

                // "Переменные" объекта
                TiXmlElement *properties;
                properties = objectElement->FirstChildElement("properties");
                if (properties != nullptr) {
                    TiXmlElement *prop;
                    prop = properties->FirstChildElement("property");
                    if (prop != nullptr) {
                        while (prop) {
                            std::string propertyName = prop->Attribute("name");
                            std::string propertyValue = prop->Attribute("value");

                            object.properties[propertyName] = propertyValue;

                            prop = prop->NextSiblingElement("property");
                        }
                    }
                }

                currLayerObjects.push_back(object);

                objectElement = objectElement->NextSiblingElement("object");
            }
            objects.push_back(currLayerObjects);

            objectGroupElement = objectGroupElement->NextSiblingElement("objectgroup");
        }
    } else {
        std::cout << "No object layers found..." << std::endl;
    }

    return true;
}

bool Level::loadStateFromFile(const std::string &filename) {
    TiXmlDocument stateFile(filename.c_str());

    // Загружаем XML
    if (!stateFile.LoadFile()) {
        std::cout << "Loading state of \"" << filename << "\" failed." << std::endl;
        return false;
    }

    return true;
}

Object Level::getObject(std::string name) {
    // Только первый объект с заданным именем
    for (auto &object : objects[currentObjectsLayer])
        if (object.name == name)
            return object;
}

std::vector<Object> Level::getObjects(std::string name) {
    // Все объекты с заданным именем
    std::vector<Object> vec;
    for (auto &object : objects[currentObjectsLayer])
        if (object.name == name)
            vec.push_back(object);

    return vec;
}

std::vector<Object> Level::getAllObjects() {
    return objects[currentObjectsLayer];
};

sf::Vector2i Level::getTileSize() const {
    return sf::Vector2i(tileWidth, tileHeight);
}

void Level::draw(sf::RenderWindow &window) {
    // Рисуем все тайлы (объекты НЕ рисуем!)
//    for (auto &layer : layers)
    for (const auto &tile : layers[currentTileLayer].tiles)
        window.draw(tile);
}

void Level::goUp() {
    if (currentTileLayer < 1) {
        currentTileLayer++;
        currentObjectsLayer++;
        std::cout << "Current tiles layer is: " << currentTileLayer << std::endl;
        std::cout << "Current objects layer is: " << currentObjectsLayer << std::endl;
    }
}

void Level::goDown() {
    if (currentTileLayer > 0) {
        currentObjectsLayer--;
        currentTileLayer--;
        std::cout << "Current tiles layer is: " << currentTileLayer << std::endl;
        std::cout << "Current objects layer is: " << currentObjectsLayer << std::endl;
    }
}

int Level::getCountOfLayers() const {
    return countOfLayers;
}

#endif
