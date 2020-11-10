#include <include/TinyXML/tinyxml.h>
#include <include/model/Player.h>
#include <list>
#include <include/model/Enemy.h>

class ObjectsParser {
public:
    static void saveToFileProgress(const Level &level, const Player &player, const std::list<Enemy *> &enemiesList) {
        TiXmlDocument doc;
        auto *decl = new TiXmlDeclaration("1.0", "utf-8", "");
        doc.LinkEndChild(decl);
        TiXmlElement *root;
        root = new TiXmlElement("map");
        root->SetAttribute("version", "1.0");
        doc.LinkEndChild(root);

        auto *image = new TiXmlElement("image");
        image->SetAttribute("source", "img/tileset_items.png");
        image->SetAttribute("width", "300");
        image->SetAttribute("height", "300");
        image->SetAttribute("tileWidth", "50");
        image->SetAttribute("tileHeight", "50");

        root->LinkEndChild(image);

        auto *objects = new TiXmlElement("objectgroup");
        root->LinkEndChild(objects);
        TiXmlElement *object;

//        for (auto layers: level.getCountOfLayers())

        for (auto enemy: enemiesList) {
            object = new TiXmlElement("object");
            object->SetAttribute("name", enemy->name.c_str());
            object->SetAttribute("type", "enemy");
            object->SetDoubleAttribute("health", enemy->health);
            object->SetDoubleAttribute("x", enemy->x);
            object->SetDoubleAttribute("y", enemy->y);
            object->SetDoubleAttribute("width", enemy->w);
            object->SetDoubleAttribute("height", enemy->h);
            objects->LinkEndChild(object);
        }

        object = new TiXmlElement("object");
        object->SetAttribute("name", player.name.c_str());
        object->SetAttribute("type", "player");
        object->SetDoubleAttribute("x", player.x);
        object->SetDoubleAttribute("y", player.y);
        object->SetDoubleAttribute("width", player.w);
        object->SetDoubleAttribute("height", player.h);

        objects->LinkEndChild(object);

        auto characteristics = new TiXmlElement("characteristics");
        root->LinkEndChild(characteristics);

        auto equipment = new TiXmlElement("equipment");
        root->LinkEndChild(equipment);

        doc.SaveFile("../res/level1objects.xml");
    }

    static void loadFromFileProgress(const Level &level, const Player &player, const std::list<Enemy *> &enemiesList) {

    }
};
