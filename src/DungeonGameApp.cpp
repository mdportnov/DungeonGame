//#pragma once

#include <include/model/Level.h>
#include "iostream"
#include "include/DungeonGameApp.h"
#include "include/model/MyView.h"
#include "include/model/Player.h"
#include "include/model/ObjectsParser.h"
#include <vector>
#include <list>
#include <include/model/Chest.h>
#include <include/model/equip/Key.h>
#include <include/model/InfoBar.h>
#include "include/model/Enemy.h"
#include "include/model/Door.h"

using namespace sf;

namespace MyGame {
    MyView myView;

    DungeonGameApp::DungeonGameApp() :
            window(nullptr) {
    }

    DungeonGameApp::~DungeonGameApp() = default;;

    void DungeonGameApp::Init() {
        window = new sf::RenderWindow(sf::VideoMode(600, 400), "DungeonGame");
        myView.view.reset(sf::FloatRect(0, 0, 600, 400));
    }

    void DungeonGameApp::Run() {
        sf::SoundBuffer buffer;
        if (!buffer.loadFromFile("../res/sound/main.ogg"))
            std::cout << "Unable to load game sound";
        sf::Sound mainSound;
        mainSound.setBuffer(buffer);
        mainSound.play();

        sf::SoundBuffer buffer1;
        if (!buffer1.loadFromFile("../res/sound/chest.wav"))
            std::cout << "Unable to load game sound";
        sf::Sound chestSound;
        chestSound.setBuffer(buffer1);

        sf::SoundBuffer buffer3;
        if (!buffer3.loadFromFile("../res/sound/door.ogg"))
            std::cout << "Unable to load game sound";
        sf::Sound doorSound;
        doorSound.setBuffer(buffer3);

        Clock clock, attackClock, doorClock, chestClock;

        Level level;
        level.loadMapFromFile("../res/level1.tmx");
        level.loadStateFromFile("../res/level1objectss.xml");

        MapObject player = level.getPlayer();
        Player p(level, myView, player.imagePath, player.name, player.rect.left, player.rect.top, player.rect.width,
                 player.rect.height);

        std::map<string, int> tmpMap;
        for (auto &a: player.properties) {
            tmpMap.insert({a.first, std::stoi(a.second)});
        }

        p.init(tmpMap);

        InfoBar infoBar;
        infoBar.observe(&p);

        vector<MapObject> enemiesObjects = level.getEnemies();
        list<Enemy *> enemiesList;

        vector<MapObject> itemsObjects = level.getItems();
        list<Item *> itemsList;

        vector<MapObject> doorsObjects = level.getDoors();
        list<Door *> doorsList;

        vector<MapObject> chestsObjects = level.getChests();
        list<Chest *> chestsList;

        for (auto &i : enemiesObjects) {
            enemiesList.push_back(
                    new Enemy(level, i.imagePath, i.name, i.rect.left, i.rect.top, i.rect.width, i.rect.height));
        }

        for (auto &i : doorsObjects) {
            doorsList.push_back(
                    new Door(level, i.imagePath, i.name, i.rect.left, i.rect.top, i.rect.width, i.rect.height));
        }

        for (auto &i : chestsObjects) {
            chestsList.push_back(
                    new Chest(level, i.imagePath, i.name, i.rect.left, i.rect.top, i.rect.width,
                              i.rect.height, std::stoi(i.properties["lockLevel"]),
                              (bool) std::stoi(i.properties["isLocked"])));
        }

        for (auto &i : itemsObjects) {
            if (i.subType == "potion") {
                vector<pair<string, int>> changesList;
                for (auto &prop : i.properties) {
                    changesList.emplace_back(prop.first, stoi(prop.second));
                }
                itemsList.push_back(
                        new Potion(level, i.imagePath, i.name, i.type, i.subType,
                                   i.rect.left, i.rect.top, i.rect.width, i.rect.height,
                                   std::stoi(i.properties["state"]),
                                   changesList));
            }
            if (i.subType == "weapon")
                itemsList.push_back(
                        new Weapon(level, i.imagePath, i.name, i.type, i.subType,
                                   i.rect.left, i.rect.top, i.rect.width, i.rect.height,
                                   std::stoi(i.properties["state"]),
                                   std::stoi(i.properties["damage"])));
            if (i.subType == "key")
                itemsList.push_back(
                        new Key(level, i.imagePath, i.name, i.type, i.subType,
                                i.rect.left, i.rect.top, i.rect.width, i.rect.height,
                                std::stoi(i.properties["state"])
                        ));
        }

        while (window->isOpen()) {
            float time = clock.getElapsedTime().asMilliseconds();
            if (Keyboard::isKeyPressed(Keyboard::A)) p.key["A"] = true;
            if (Keyboard::isKeyPressed(Keyboard::D)) p.key["D"] = true;
            if (Keyboard::isKeyPressed(Keyboard::W)) p.key["W"] = true;
            if (Keyboard::isKeyPressed(Keyboard::S)) p.key["S"] = true;

            Event event;
            bool ladderUsed = false;
            if (time > 60) {
                clock.restart();

                while (window->pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        window->close();
                    if (p.STATE == Player::STATE::onladderup && !ladderUsed) {
                        level.goUp();
                        p.STATE = Player::STATE::stay;
                        p.map = level.getAllMapObjects();
                        ladderUsed = true;
                    }
                    if (p.STATE == Player::STATE::onladderdown && !ladderUsed) {
                        level.goDown();
                        p.STATE = Player::STATE::stay;
                        p.map = level.getAllMapObjects();
                        ladderUsed = true;
                    }
                    if (Keyboard::isKeyPressed(Keyboard::P)) {
                        if (p.currentPotion == 3) {
                            p.currentPotion = 0;
                            break;
                        } else {
                            p.currentPotion++;
                            break;
                        }
                    }
                }

                p.update(time);

                for (auto it = enemiesList.begin(); it != enemiesList.end(); it++) {
                    Enemy *b = *it;
                    b->update(time);
                    if (!b->isAlive) {
                        it = enemiesList.erase(it);
                        delete b;
                    }
                }

                if (doorClock.getElapsedTime().asMilliseconds() > 200) {
                    for (auto b : doorsList) {
                        if (p.getRect().intersects(b->getRect()) && b->isLocked) {
                            if (p.dy > 0) {
                                p.y = b->getRect().top - p.h;
                                p.dy = 0;
                            }
                            if (p.dy < 0) {
                                p.y = b->getRect().top + b->getRect().height;
                                p.dy = 0;
                            }
                            if (p.dx > 0) { p.x = b->getRect().left - p.w; }
                            if (p.dx < 0) { p.x = b->getRect().left + b->getRect().width; }
                        }

                        if (p.getRect().intersects(b->getAreaRect())) {
                            if (Mouse::isButtonPressed(sf::Mouse::Left)) {
                                b->changeDoorState();
                                doorSound.play();
                                doorClock.restart();
                            }
                        }
                        b->update();
                    }
                }

                if (chestClock.getElapsedTime().asMilliseconds() > 50) {
                    for (auto b : chestsList) {
                        if (p.getRect().intersects(b->getAreaRect())) {
                            if (Mouse::isButtonPressed(sf::Mouse::Left) && b->isLocked) {
                                b->open(p);
                                chestSound.play();
                                chestClock.restart();
                            }
                        }
                        b->update(time);
                    }
                }

                for (auto it = itemsList.begin(); it != itemsList.end(); it++) {
                    Item *b = *it;

                    if (p.getRect().intersects(b->getRect()) && b->state != Item::STATE::onMe) {
                        p.takeItem(b);
                    }

                    b->update(time);
                    if (b->state == Item::STATE::nowhere) {
                        it = itemsList.erase(it);
                        delete b;
                    }
                }

                if (attackClock.getElapsedTime().asMilliseconds() > 100)
                    for (auto &it : enemiesList) {
                        if (p.getRect().intersects(it->getRect())) {
                            if (p.dx > 0) {
                                it->dx = 0.1;
                            }

                            if (p.dx < 0) {
                                it->dx = -0.1;
                            }

                            if (p.dy > 0) {
                                it->dy = 0.1;
                            }

                            if (p.dy < 0) {
                                it->dy = -0.1;
                            }
                            it->update(time);
                            it->dx = 0;
                            it->dy = 0;
                            it->acceptDamageFrom(p);
                            p.acceptDamageFrom(*it);
                            attackClock.restart();
                        }
                    }
            }

            myView.viewMap(time);
            myView.changeView();
            window->setView(myView.view);
            window->clear(sf::Color(169, 169, 169));

            level.draw(*window);

            for (auto enemy : enemiesList) {
//                if ((*enemy).name == "egorov") {
//                    RectangleShape rect(Vector2f(enemy->getEnemyArea().width, enemy->getEnemyArea().height));
//                    rect.setPosition(enemy->x - enemy->getEnemyArea().width / 2 + enemy->w / 2,
//                                     enemy->y - enemy->getEnemyArea().height / 2 + enemy->h / 2);
//                    rect.setOutlineThickness(5);
//                    rect.setFillColor(Color::Transparent);
//                    rect.setOutlineColor(sf::Color(250, 150, 100));
//                    window->draw(rect);
//                }
                enemy->draw(*window);
            }
            for (auto door: doorsList) {
                door->draw(*window);
            }
            for (auto chest: chestsList) {
                chest->draw(*window);
            }
            for (auto item: itemsList) {
                if (item->state == Item::onMap)
                    item->draw(*window);
            }

            infoBar.draw(*window);
            p.draw(*window);
            window->display();
            ObjectsParser::saveToFileProgress(level, p, enemiesList, itemsList, doorsList, chestsList);
        }
    }

    void DungeonGameApp::End() {
        if (window != nullptr) {
            delete window;
            window = nullptr;
        }
    }

    void DungeonGameApp::playSound(string name) {

    }
}
