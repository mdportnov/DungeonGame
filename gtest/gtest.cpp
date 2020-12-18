#include <src/HashMap.h>
#include <include/model/Level.h>
#include <include/model/Player.h>
#include <include/model/Enemy.h>
#include <include/model/equip/EnchantedWeapon.h>
#include <include/model/equip/ArtefactWeapon.h>
#include <include/model/equip/ArtefactEquipment.h>
#include <include/model/Chest.h>
#include "gtest/gtest.h"

#pragma once

TEST(Map, MapCheck) {
    HashMap<string, float> map;
    map.insert("sp", 0.1);
    map.insert("hp", 200.0);
    ASSERT_FLOAT_EQ(map["sp"], 0.1);
    ASSERT_FLOAT_EQ(map["hp"], 200.0);
}

TEST(Player, Attributes) {
    Level level;
    level.loadStaticMapFromFile("../res/level1.tmx");
    level.loadDynamicObjectsFromFile("../res/level1objects.xml");
    MyView myView;
    MapObject player = level.getPlayer();

    Player p = Player(level, myView, player.imagePath, player.name, player.rect.left, player.rect.top,
                      player.rect.width,
                      player.rect.height, player.layer, player.properties);

    ASSERT_FLOAT_EQ(p.x, 156);
    ASSERT_FLOAT_EQ(p.attributes["sp"], 0.1);
    ASSERT_FLOAT_EQ(p.attributes["hp"], 200);
}

TEST(Door, Actions) {
    Level level;
    level.loadStaticMapFromFile("../res/level1.tmx");
    level.loadDynamicObjectsFromFile("../res/level1objects.xml");

    Door *door;
    for (auto i : level.getObjectsByType("door")) {
        door = new Door(level, i.imagePath, i.name, i.rect.left, i.rect.top, i.rect.width, i.rect.height, i.layer,
                        (bool) std::stoi(i.properties["isLocked"]));
        break;
    }

    ASSERT_EQ(door->isLocked, true);
    door->changeDoorState();
    ASSERT_EQ(door->isLocked, false);
}

TEST(Chest, Actions) {
    Level level;
    level.loadStaticMapFromFile("../res/level1.tmx");
    level.loadDynamicObjectsFromFile("../res/level1objects.xml");

    MyView myView;
    MapObject player = level.getPlayer();

    Player p = Player(level, myView, player.imagePath, player.name, player.rect.left, player.rect.top,
                      player.rect.width,
                      player.rect.height, player.layer, player.properties);

    Chest *chest;
    for (auto i : level.getObjectsByType("chest")) {
        chest = new Chest(level, i.imagePath, i.name, i.rect.left, i.rect.top, i.rect.width,
                          i.rect.height, i.layer, std::stoi(i.properties["lockLevel"]),
                          (bool) std::stoi(i.properties["isLocked"]));
        break;
    }

    Item *item;

    for (auto i : level.getObjectsByType("item")) {
        if (i.name == "armor_breastplate_diamond")
            item = new Equipment(level, i.imagePath, i.name, i.type, i.subType,
                                 i.rect.left, i.rect.top, i.rect.width, i.rect.height,
                                 i.layer,
                                 std::stoi(i.properties["state"]),
                                 std::stof(i.properties["protection"]),
                                 std::stoi(i.properties["eqType"]),
                                 std::stoi(i.properties["materialType"])
            );
    }


    chest->setItem(item);

    p.bunchOfKeys.addNewOne();

    ASSERT_EQ(chest->isLocked, true);
    chest->open(p);
    ASSERT_EQ(chest->isLocked, false);
}

TEST(Potion, ChangeCharacterictics) {
    Level level;
    level.loadStaticMapFromFile("../res/level1.tmx");
    level.loadDynamicObjectsFromFile("../res/level1objects.xml");
    MyView myView;
    MapObject player = level.getPlayer();

    Player p = Player(level, myView, player.imagePath, player.name, player.rect.left, player.rect.top,
                      player.rect.width,
                      player.rect.height, player.layer, player.properties);

    Item *potion;

    for (auto i : level.getObjectsByType("item")) {
        if (i.subType == "potion") {
            potion = new Potion(level, i.imagePath, i.name, i.type, i.subType,
                                i.rect.left, i.rect.top, i.rect.width, i.rect.height, i.layer,
                                std::stoi(i.properties["state"]), i.properties);
            break;
        }
    }

    p.takeItem(potion);
    p.attributes[p.drinkPotion()[0].first] += p.drinkPotion()[0].second;

    ASSERT_FLOAT_EQ(40, p.attributes[p.drinkPotion()[0].first]);
}

TEST(Weapon, ChangeCharacterictics) {
    Level level;
    level.loadStaticMapFromFile("../res/level1.tmx");
    level.loadDynamicObjectsFromFile("../res/level1objects.xml");
    MyView myView;
    MapObject player = level.getPlayer();

    Player p = Player(level, myView, player.imagePath, player.name, player.rect.left, player.rect.top,
                      player.rect.width,
                      player.rect.height, player.layer, player.properties);

    Item *weapon;

    for (auto i : level.getObjectsByType("item")) {
        if (i.subType == "weapon") {
            weapon = new Weapon(level, i.imagePath, i.name, i.type, i.subType,
                                i.rect.left, i.rect.top, i.rect.width, i.rect.height, i.layer,
                                std::stoi(i.properties["state"]),
                                std::stof(i.properties["damage"]));
            break;
        }
    }

    Enemy *enemy;

    for (auto i : level.getObjectsByType("enemy")) {
        enemy = new Enemy(level, i.imagePath, i.name, i.rect.left, i.rect.top, i.rect.width, i.rect.height, i.layer,
                          i.properties);
        break;
    }

    p.takeItem(weapon);

    ASSERT_FLOAT_EQ(50, p.calculateDamage(enemy));

    for (auto i : level.getObjectsByType("item")) {
        if (i.subType == "eweapon") {
            weapon = new EnchantedWeapon(level, i.imagePath, i.name, i.type, i.subType,
                                         i.rect.left, i.rect.top, i.rect.width, i.rect.height,
                                         i.layer,
                                         std::stoi(i.properties["state"]),
                                         std::stof(i.properties["damage"]),
                                         i.properties
            );
            break;
        }
    }
    p.takeItem(weapon);
    enemy->acceptDamageFrom(&p);

    ASSERT_TRUE(enemy->health < 0); // снеслись все hp тк оружие против этого персонажа

    for (auto i : level.getObjectsByType("item")) {
        if (i.subType == "aweapon") {
            weapon = new ArtefactWeapon(level, i.imagePath, i.name, i.type, i.subType,
                                        i.rect.left, i.rect.top, i.rect.width, i.rect.height,
                                        i.layer,
                                        std::stoi(i.properties["state"]),
                                        std::stof(i.properties["damage"]),
                                        i.properties
            );
            break;
        }
    }
    p.takeItem(weapon);

    ASSERT_FLOAT_EQ(p.getSkillValue("dx"), 0.6);
}

TEST(Equipment, ChangeCharacterictics) {
    Level level;
    level.loadStaticMapFromFile("../res/level1.tmx");
    level.loadDynamicObjectsFromFile("../res/level1objects.xml");
    MyView myView;
    MapObject player = level.getPlayer();

    Player p = Player(level, myView, player.imagePath, player.name, player.rect.left, player.rect.top,
                      player.rect.width,
                      player.rect.height, player.layer, player.properties);

    Item *equip;

    for (auto i : level.getObjectsByType("item")) {
        if (i.subType == "aequipment") {
            equip = new ArtefactEquipment(level, i.imagePath, i.name, i.type, i.subType,
                                          i.rect.left, i.rect.top, i.rect.width, i.rect.height,
                                          i.layer,
                                          std::stoi(i.properties["state"]),
                                          std::stof(i.properties["protection"]),
                                          std::stoi(i.properties["eqType"]),
                                          std::stoi(i.properties["materialType"]),
                                          i.properties
            );
            break;
        }
    }

    ASSERT_FLOAT_EQ(p.getSkillValue("sp"), 0.1);
    ASSERT_FLOAT_EQ(p.calculateProtection(), 0.5);

    p.takeItem(equip);
    ASSERT_FLOAT_EQ(p.getSkillValue("sp"), 0.13);
    ASSERT_FLOAT_EQ(p.calculateProtection(), 20.5);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}