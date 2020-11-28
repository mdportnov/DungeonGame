#pragma once

#include <include/TinyXML/tinyxml.h>
#include <include/model/Player.h>
#include <list>
#include <include/model/Enemy.h>
#include <include/model/equip/Key.h>
#include <include/model/equip/ArtefactEquipment.h>
#include <include/model/equip/ArtefactWeapon.h>
#include <include/model/equip/EnchantedWeapon.h>
#include "Door.h"
#include "Chest.h"

class ObjectsParser {
public:
    static void saveToFileProgress(const Level &level, const Player &player, const list<Enemy *> &enemiesList,
                                   const list<Item *> &itemsList, list<Door *> &doorsList, list<Chest *> chestsList) {
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

        // Герой
        object = new TiXmlElement("object");
        object->SetAttribute("name", player.name.c_str());
        object->SetAttribute("type", "player");
        object->SetDoubleAttribute("x", player.x);
        object->SetDoubleAttribute("y", player.y);
        object->SetDoubleAttribute("width", player.w);
        object->SetDoubleAttribute("height", player.h);
        object->SetAttribute("layer", player.layer);

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

//        for (auto layers: level.getCountOfLayers())
        // ВРАГИ
        for (auto it: enemiesList) {
            object = new TiXmlElement("object");
            object->SetAttribute("name", it->name.c_str());
            object->SetAttribute("type", "enemy");
            object->SetDoubleAttribute("x", it->x);
            object->SetDoubleAttribute("y", it->y);
            object->SetDoubleAttribute("width", it->w);
            object->SetDoubleAttribute("height", it->h);
            object->SetAttribute("layer", it->layer);

            auto *property = new TiXmlElement("property");
            auto *properties = new TiXmlElement("properties");

            property = new TiXmlElement("property");
            property->SetAttribute("name", "hp");
            property->SetDoubleAttribute("value", it->health);
            properties->LinkEndChild(property);

            property = new TiXmlElement("property");
            property->SetAttribute("name", "lvl");
            property->SetDoubleAttribute("value", it->lvl);
            properties->LinkEndChild(property);

            property = new TiXmlElement("property");
            property->SetAttribute("name", "damage");
            property->SetDoubleAttribute("value", it->damage);
            properties->LinkEndChild(property);

            object->LinkEndChild(properties);
            objects->LinkEndChild(object);
        }

        for (auto &it: doorsList) {
            object = new TiXmlElement("object");
            object->SetAttribute("name", it->name.c_str());
            object->SetAttribute("type", "door");
            object->SetDoubleAttribute("x", it->x);
            object->SetDoubleAttribute("y", it->y);
            object->SetDoubleAttribute("width", it->w);
            object->SetDoubleAttribute("height", it->h);
            object->SetAttribute("layer", it->layer);

            properties = new TiXmlElement("properties");
            auto *property = new TiXmlElement("property");
            property = new TiXmlElement("property");
            property->SetAttribute("name", "isLocked");
            property->SetAttribute("value", to_string(it->isLocked).c_str());
            properties->LinkEndChild(property);

            object->LinkEndChild(properties);

            objects->LinkEndChild(object);
        }

        for (auto &it: chestsList) {
            object = new TiXmlElement("object");
            object->SetAttribute("name", it->name.c_str());
            object->SetAttribute("type", "chest");
            object->SetDoubleAttribute("x", it->x);
            object->SetDoubleAttribute("y", it->y);
            object->SetDoubleAttribute("width", it->w);
            object->SetDoubleAttribute("height", it->h);
            object->SetAttribute("layer", it->layer);


            properties = new TiXmlElement("properties");
            auto *property = new TiXmlElement("property");
            property->SetAttribute("name", "lockLevel");
            property->SetAttribute("value", to_string(it->lockLevel).c_str());
            properties->LinkEndChild(property);

            property = new TiXmlElement("property");
            property->SetAttribute("name", "isLocked");
            property->SetAttribute("value", to_string(it->isLocked).c_str());
            properties->LinkEndChild(property);

            object->LinkEndChild(properties);
            objects->LinkEndChild(object);
        }

        // Оружие, зелья, ключи
        for (auto &it: itemsList) {
            object = new TiXmlElement("object");

            properties = new TiXmlElement("properties");

            object->SetAttribute("name", it->name.c_str());
            object->SetAttribute("type", "item");
            object->SetAttribute("subType", it->subType.c_str());
            object->SetDoubleAttribute("x", it->x);
            object->SetDoubleAttribute("y", it->y);
            object->SetDoubleAttribute("width", it->w);
            object->SetDoubleAttribute("height", it->h);
            object->SetAttribute("layer", it->layer);

            auto *property = new TiXmlElement("property");

            if (dynamic_cast<Weapon *>(it) != nullptr) {
                property = new TiXmlElement("property");
                property->SetAttribute("name", "damage");
                property->SetAttribute("value", to_string((int) dynamic_cast<Weapon *>(it)->calculateDamage()).c_str());
                properties->LinkEndChild(property);

                if (dynamic_cast<ArtefactWeapon *>(it) != nullptr) {
                    for (const auto& a : dynamic_cast<ArtefactWeapon *>(it)->changesListA) {
                        property = new TiXmlElement("property");
                        property->SetAttribute("name", (a.first).c_str());
                        property->SetAttribute("value", to_string(a.second).c_str());
                        properties->LinkEndChild(property);
                    }
                }

                if (dynamic_cast<EnchantedWeapon *>(it) != nullptr) {
                    for (const auto& a : dynamic_cast<EnchantedWeapon *>(it)->changesListE) {
                        property = new TiXmlElement("property");
                        property->SetAttribute("name", (a.first).c_str());
                        property->SetAttribute("value", to_string(a.second).c_str());
                        properties->LinkEndChild(property);
                    }
                }
            }
            if (dynamic_cast<Potion *>(it) != nullptr)
                for (auto &i:  dynamic_cast<Potion *>(it)->changesListA) {
                    property = new TiXmlElement("property");
                    property->SetAttribute("name", (i.first).c_str());
                    property->SetAttribute("value", to_string(i.second).c_str());
                    properties->LinkEndChild(property);
                }

            if (dynamic_cast<Equipment *>(it) != nullptr) {
                auto i = dynamic_cast<Equipment *>(it);
                property = new TiXmlElement("property");
                property->SetAttribute("name", "protection");
                property->SetAttribute("value", to_string(i->protection).c_str());
                properties->LinkEndChild(property);

                property = new TiXmlElement("property");
                property->SetAttribute("name", "eqType");
                property->SetAttribute("value", i->eqType);
                properties->LinkEndChild(property);

                property = new TiXmlElement("property");
                property->SetAttribute("name", "materialType");
                property->SetAttribute("value", i->materialType);
                properties->LinkEndChild(property);

                if (dynamic_cast<ArtefactEquipment *>(it) != nullptr) {
                    for (auto a : dynamic_cast<ArtefactEquipment *>(it)->changesListA) {
                        property = new TiXmlElement("property");
                        property->SetAttribute("name", a.first.c_str());
                        property->SetAttribute("value", to_string(a.second).c_str());
                        properties->LinkEndChild(property);
                    }
                }
            }

            property = new TiXmlElement("property");

            property->SetAttribute("name", "state");
            property->SetAttribute("value", it->state);
            properties->LinkEndChild(property);

            object->LinkEndChild(properties);
            objects->LinkEndChild(object);
        }

        doc.SaveFile("../res/level1objectss.xml");
    }

    void loadFromFileProgress(const Level &level, const Player &player, const std::list<Enemy *> &enemiesList) {

    }

};
