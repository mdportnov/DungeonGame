#include <iostream>
#include <tinyxml.h>
#include "main.h"

struct Object {
    int getPropertyInt(std::string name);

    float getPropertyFloat(std::string name);

    std::string getPropertyString(std::string name);

    std::string name;
    std::string type;
    sf::Rect<int> rect;
    std::map<std::string, std::string> properties;

    sf::Sprite sprite;
};

struct Layer//слои
{
    int opacity;//непрозрачность слоя
    std::vector<sf::Sprite> tiles;//закидываем в вектор тайлы
};


class Level//главный класс - уровень
{
public:
    bool loadFromFile(std::string filename);//возвращает false если не получилось загрузить
    Object getObject(std::string name);
    std::vector<Object> getObjects(std::string name);//выдаем объект в наш уровень
    std::vector<Object> getAllObjects();//выдаем все объекты в наш уровень
    void Draw(sf::RenderWindow &window);//рисуем в окно
    sf::Vector2i GetTileSize();//получаем размер тайла

private:
    int width, height, tileWidth, tileHeight;//в tmx файле width height в начале,затем размер тайла
    int firstTileID; //получаем айди первого тайла
    sf::Rect<float> drawingBounds; //размер части карты которую рисуем
    sf::Texture tileSetImage;//текстура карты
    std::vector<Object> objects;//массив типа Объекты, который мы создали
    std::vector<Layer> layers;
};

int Object::getPropertyInt(std::string name)//возвращаем номер свойства в нашем списке
{
    return atoi(properties[name].c_str());
}

float Object::getPropertyFloat(std::string name)
{
    return strtod(properties[name].c_str(), nullptr);
}

std::string Object::getPropertyString(std::string name)//получить имя в виде строки.вроде понятно
{
    return properties[name];
}

bool Level::loadFromFile(std::string filename)//двоеточия-обращение к методам класса вне класса
{
    TiXmlDocument levelFile(filename.c_str());//загружаем файл в TiXmlDocument

    // загружаем XML-карту
    if (!levelFile.LoadFile())//если не удалось загрузить карту
    {
        std::cout << "Loading level \"" << filename << "\" failed." << std::endl;//выдаем ошибку
        return false;
    }

    // работаем с контейнером map
    TiXmlElement *map;
    map = levelFile.FirstChildElement("map");

    // пример карты: <map version="1.0" orientation="orthogonal"
    // width="10" height="10" tilewidth="34" tileheight="34">
    width = atoi(map->Attribute("width"));//извлекаем из нашей карты ее свойства
    height = atoi(map->Attribute("height"));//те свойства, которые задавали при работе в
    tileWidth = atoi(map->Attribute("tilewidth"));//тайлмап редакторе
    tileHeight = atoi(map->Attribute("tileheight"));

    // Берем описание тайлсета и идентификатор первого тайла
    TiXmlElement *tilesetElement;
    tilesetElement = map->FirstChildElement("tileset");
    firstTileID = atoi(tilesetElement->Attribute("firstgid"));

    // source - путь до картинки в контейнере image
    TiXmlElement *image;
    image = tilesetElement->FirstChildElement("image");
    std::string imagepath = image->Attribute("source");

    // пытаемся загрузить тайлсет
    sf::Image img;

    if (!img.loadFromFile(imagepath))
    {
        std::cout << "Failed to load tile sheet." << std::endl;//если не удалось загрузить тайлсет-выводим ошибку в консоль
        return false;
    }

    img.createMaskFromColor(sf::Color(255, 255, 255));//для маски цвета.сейчас нет маски
    tileSetImage.loadFromImage(img);
    tileSetImage.setSmooth(false);//сглаживание

    // получаем количество столбцов и строк тайлсета
    int columns = tileSetImage.getSize().x / tileWidth;
    int rows = tileSetImage.getSize().y / tileHeight;

    // вектор из прямоугольников изображений (TextureRect)
    std::vector<sf::Rect<int>> subRects;

    for (int y = 0; y < rows; y++)
        for (int x = 0; x < columns; x++)
        {
            sf::Rect<int> rect;

            rect.top = y * tileHeight;
            rect.height = tileHeight;
            rect.left = x * tileWidth;
            rect.width = tileWidth;

            subRects.push_back(rect);
        }

    // работа со слоями
    TiXmlElement *layerElement;
    layerElement = map->FirstChildElement("layer");
    while (layerElement)
    {
        Layer layer;

        // если присутствует opacity, то задаем прозрачность слоя, иначе он полностью непрозрачен
        if (layerElement->Attribute("opacity") != nullptr)
        {
            float opacity = strtod(layerElement->Attribute("opacity"), nullptr);
            layer.opacity = 255 * opacity;
        }
        else
        {
            layer.opacity = 255;
        }

        //  контейнер <data>
        TiXmlElement *layerDataElement;
        layerDataElement = layerElement->FirstChildElement("data");

        if (layerDataElement == nullptr)
        {
            std::cout << "Bad map. No layer information found." << std::endl;
        }

        //  контейнер <tile> - описание тайлов каждого слоя
        TiXmlElement *tileElement;
        tileElement = layerDataElement->FirstChildElement("tile");

        if (tileElement == nullptr)
        {
            std::cout << "Bad map. No tile information found." << std::endl;
            return false;
        }

        int x = 0;
        int y = 0;

        while (tileElement)
        {
            int tileGID = atoi(tileElement->Attribute("gid"));
            int subRectToUse = tileGID - firstTileID;

            // Устанавливаем TextureRect каждого тайла
            if (subRectToUse >= 0)
            {
                sf::Sprite sprite;
                sprite.setTexture(tileSetImage);
                sprite.setTextureRect(subRects[subRectToUse]);
                sprite.setPosition(x * tileWidth, y * tileHeight);
                sprite.setColor(sf::Color(255, 255, 255, layer.opacity));

                layer.tiles.push_back(sprite);//закидываем в слой спрайты тайлов
            }

            tileElement = tileElement->NextSiblingElement("tile");

            x++;
            if (x >= width)
            {
                x = 0;
                y++;
                if (y >= height)
                    y = 0;
            }
        }

        layers.push_back(layer);

        layerElement = layerElement->NextSiblingElement("layer");
    }

    // работа с объектами
    TiXmlElement *objectGroupElement;

    // если есть слои объектов
    if (map->FirstChildElement("objectgroup") != nullptr)
    {
        objectGroupElement = map->FirstChildElement("objectgroup");
        while (objectGroupElement)
        {
            //  контейнер <object>
            TiXmlElement *objectElement;
            objectElement = objectGroupElement->FirstChildElement("object");

            while (objectElement)
            {
                // получаем все данные - тип, имя, позиция, и тд
                std::string objectType;
                if (objectElement->Attribute("type") != nullptr)
                {
                    objectType = objectElement->Attribute("type");
                }
                std::string objectName;
                if (objectElement->Attribute("name") != nullptr)
                {
                    objectName = objectElement->Attribute("name");
                }
                int x = atoi(objectElement->Attribute("x"));
                int y = atoi(objectElement->Attribute("y"));

                int width, height;

                sf::Sprite sprite;
                sprite.setTexture(tileSetImage);
                sprite.setTextureRect(sf::Rect<int>(0, 0, 0, 0));
                sprite.setPosition(x, y);

                if (objectElement->Attribute("width") != nullptr)
                {
                    width = atoi(objectElement->Attribute("width"));
                    height = atoi(objectElement->Attribute("height"));
                }
                else
                {
                    width = subRects[atoi(objectElement->Attribute("gid")) - firstTileID].width;
                    height = subRects[atoi(objectElement->Attribute("gid")) - firstTileID].height;
                    sprite.setTextureRect(subRects[atoi(objectElement->Attribute("gid")) - firstTileID]);
                }

                // экземпляр объекта
                Object object;
                object.name = objectName;
                object.type = objectType;
                object.sprite = sprite;

                sf::Rect <int> objectRect;
                objectRect.top = y;
                objectRect.left = x;
                objectRect.height = height;
                objectRect.width = width;
                object.rect = objectRect;

                // "переменные" объекта
                TiXmlElement *properties;
                properties = objectElement->FirstChildElement("properties");
                if (properties != nullptr)
                {
                    TiXmlElement *prop;
                    prop = properties->FirstChildElement("property");
                    if (prop != nullptr)
                    {
                        while (prop)
                        {
                            std::string propertyName = prop->Attribute("name");
                            std::string propertyValue = prop->Attribute("value");

                            object.properties[propertyName] = propertyValue;

                            prop = prop->NextSiblingElement("property");
                        }
                    }
                }


                objects.push_back(object);

                objectElement = objectElement->NextSiblingElement("object");
            }
            objectGroupElement = objectGroupElement->NextSiblingElement("objectgroup");
        }
    }
    else
    {
        std::cout << "No object layers found..." << std::endl;
    }

    return true;
}

Object Level::getObject(std::string name)
{
    // только первый объект с заданным именем
    for (int i = 0; i < objects.size(); i++)
        if (objects[i].name == name)
            return objects[i];
}

std::vector<Object> Level::getObjects(std::string name)
{
    // все объекты с заданным именем
    std::vector<Object> vec;
    for (auto & object : objects)
        if (object.name == name)
            vec.push_back(object);

    return vec;
}


std::vector<Object> Level::getAllObjects()
{
    return objects;
};


sf::Vector2i Level::GetTileSize()
{
    return sf::Vector2i(tileWidth, tileHeight);
}

void Level::Draw(sf::RenderWindow &window)
{
    // рисуем все тайлы (объекты не рисуем!)
    for (auto & layer : layers)
        for (const auto & tile : layer.tiles)
            window.draw(tile);
}