#pragma once

#include <include/TinyXML/tinyxml.h>
#include <include/model/Player.h>
#include <list>
#include <include/model/Enemy.h>
#include <include/model/equip/Key.h>
#include "Door.h"

class ObjectsParser {
public:
    static void saveToFileProgress(const Level &level, const Player &player, const list<Enemy *> &enemiesList,
                                   const list<Item *> &itemsList, list<Door *> &doorsList) {
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
        // ВРАГИ
        for (auto it: enemiesList) {
            object = new TiXmlElement("object");
            object->SetAttribute("name", it->name.c_str());
            object->SetAttribute("type", "enemy");
            object->SetDoubleAttribute("health", it->health);
            object->SetDoubleAttribute("x", it->x);
            object->SetDoubleAttribute("y", it->y);
            object->SetDoubleAttribute("width", it->w);
            object->SetDoubleAttribute("height", it->h);
            objects->LinkEndChild(object);
        }

        // Герой
        object = new TiXmlElement("object");
        object->SetAttribute("name", player.name.c_str());
        object->SetAttribute("type", "player");
        object->SetDoubleAttribute("x", player.x);
        object->SetDoubleAttribute("y", player.y);
        object->SetDoubleAttribute("width", player.w);
        object->SetDoubleAttribute("height", player.h);

        // Характеристики героя
        auto *properties = new TiXmlElement("properties");
        for (auto &a: player.attributes) {
            auto *property = new TiXmlElement("property");
            property->SetAttribute("name", (a.first).c_str());
            property->SetAttribute("value", to_string(a.second).c_str());
            properties->LinkEndChild(property);
        }
        object->LinkEndChild(properties);
        objects->LinkEndChild(object);

        for (auto &it: doorsList) {
            object = new TiXmlElement("object");
            object->SetAttribute("name", it->name.c_str());
            object->SetAttribute("type", "door");
            object->SetDoubleAttribute("x", it->x);
            object->SetDoubleAttribute("y", it->y);
            object->SetDoubleAttribute("width", it->w);
            object->SetDoubleAttribute("height", it->h);
            objects->LinkEndChild(object);
        }

        // Оружие, зелья, ключи
        for (auto &it: itemsList) {
            object = new TiXmlElement("object");

            properties = new TiXmlElement("properties");
            string name;
            string value;

            object->SetAttribute("name", it->name.c_str());
            object->SetAttribute("type", "item");
            object->SetAttribute("subType", it->subType.c_str());
            object->SetDoubleAttribute("x", it->x);
            object->SetDoubleAttribute("y", it->y);
            object->SetDoubleAttribute("width", it->w);
            object->SetDoubleAttribute("height", it->h);

            if (dynamic_cast<Weapon *>(it) != nullptr) {
                auto *property = new TiXmlElement("property");

                property->SetAttribute("name", "damage");
                property->SetAttribute("value", to_string(dynamic_cast<Weapon *>(it)->getDamage()).c_str());
                properties->LinkEndChild(property);
            }
            if (dynamic_cast<Potion *>(it) != nullptr)
                for (auto &i:  dynamic_cast<Potion *>(it)->changesList) {
                    auto *property = new TiXmlElement("property");
                    property->SetAttribute("name", (i.first).c_str());
                    property->SetAttribute("value", to_string(i.second).c_str());
                    properties->LinkEndChild(property);
                }
            object->LinkEndChild(properties);
            objects->LinkEndChild(object);
        }

//        auto equipment = new TiXmlElement("equipment");
//        root->LinkEndChild(equipment);

        doc.SaveFile("../res/level1objectss.xml");
    }

    static void loadFromFileProgress(const Level &level, const Player &player, const std::list<Enemy *> &enemiesList) {

    }
};