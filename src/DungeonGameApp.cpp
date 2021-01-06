#include <include/model/Level.h>
#include "iostream"
#include "include/DungeonGameApp.h"
#include "include/model/MyView.h"
#include "include/model/Player.h"
#include "include/model/ObjectsParser.h"
#include <list>
#include <include/model/Chest.h>
#include <include/model/equip/Key.h>
#include <include/model/InfoBar.h>
#include <include/model/equip/ArtefactWeapon.h>
#include <include/model/equip/ArtefactEquipment.h>
#include <include/model/equip/EnchantedWeapon.h>
#include <include/model/equip/EnchantedArtefactWeapon.h>
#include "include/model/Enemy.h"
#include "include/model/Door.h"

using namespace sf;

MyView myView;
sf::RenderWindow *window;

DungeonGameApp::DungeonGameApp() {}

DungeonGameApp::~DungeonGameApp() = default;

void DungeonGameApp::MusicInit() {
    if (!buffer1.loadFromFile("../res/sound/main.ogg"))
        std::cout << "Unable to load game sound";
    mainSound.setBuffer(buffer1);
//        mainSound.play();

    if (!buffer2.loadFromFile("../res/sound/chest.wav"))
        std::cout << "Unable to load game sound";
    chestSound.setBuffer(buffer2);

    if (!buffer3.loadFromFile("../res/sound/door.ogg"))
        std::cout << "Unable to load game sound";
    doorSound.setBuffer(buffer3);
}

void DungeonGameApp::Init() {
    window = new sf::RenderWindow(sf::VideoMode(600, 400), "DungeonGame");
    myView.view.reset(sf::FloatRect(0, 0, 600, 400));
}

void DungeonGameApp::Run() {
    MusicInit();
    Clock clock, attackClock, doorClock, chestClock, potionsClock, ladderClock, usingPotionClock, itemsClock;

    Level level;
    level.loadStaticMapFromFile("../res/level1.tmx");
    level.loadDynamicObjectsFromFile("../res/level1objects.xml");

    MapObject player = level.getPlayer();

    Player p = Player(level, myView, player.imagePath, player.name, player.rect.left, player.rect.top,
                      player.rect.width,
                      player.rect.height, player.layer, player.properties);

    InfoBar infoBar;
    infoBar.observe(&p);

    list<Enemy *> enemiesList;

    list<Item *> itemsList;

    list<Door *> doorsList;

    list<Chest *> chestsList;

    for (auto i : level.getObjectsByType("enemy")) {
        enemiesList.push_back(
                new Enemy(level, i.imagePath, i.name, i.rect.left, i.rect.top, i.rect.width, i.rect.height, i.layer,
                          i.properties));
    }

    for (auto i : level.getObjectsByType("door")) {
        doorsList.push_back(
                new Door(level, i.imagePath, i.name, i.rect.left, i.rect.top, i.rect.width, i.rect.height, i.layer,
                         (bool) std::stoi(i.properties["isLocked"])));
    }

    for (auto i : level.getObjectsByType("chest")) {
        chestsList.push_back(
                new Chest(level, i.imagePath, i.name, i.rect.left, i.rect.top, i.rect.width,
                          i.rect.height, i.layer, std::stoi(i.properties["lockLevel"]),
                          (bool) std::stoi(i.properties["isLocked"])));
    }

    for (auto i : level.getObjectsByType("item")) {
        if (i.subType == "potion") {
            itemsList.push_back(
                    new Potion(level, i.imagePath, i.name, i.type, i.subType,
                               i.rect.left, i.rect.top, i.rect.width, i.rect.height, i.layer,
                               std::stoi(i.properties["state"]), i.properties));
        }
        if (i.subType == "weapon")
            itemsList.push_back(
                    new Weapon(level, i.imagePath, i.name, i.type, i.subType,
                               i.rect.left, i.rect.top, i.rect.width, i.rect.height, i.layer,
                               std::stoi(i.properties["state"]),
                               std::stof(i.properties["damage"])));
        if (i.subType == "aweapon")
            itemsList.push_back(
                    new ArtefactWeapon(level, i.imagePath, i.name, i.type, i.subType,
                                       i.rect.left, i.rect.top, i.rect.width, i.rect.height, i.layer,
                                       std::stoi(i.properties["state"]),
                                       std::stof(i.properties["damage"]),
                                       i.properties
                    ));
        if (i.subType == "eweapon")
            itemsList.push_back(
                    new EnchantedWeapon(level, i.imagePath, i.name, i.type, i.subType,
                                        i.rect.left, i.rect.top, i.rect.width, i.rect.height,
                                        i.layer,
                                        std::stoi(i.properties["state"]),
                                        std::stof(i.properties["damage"]),
                                        i.properties
                    ));
        if (i.subType == "equipment")
            itemsList.push_back(
                    new Equipment(level, i.imagePath, i.name, i.type, i.subType,
                                  i.rect.left, i.rect.top, i.rect.width, i.rect.height,
                                  i.layer,
                                  std::stoi(i.properties["state"]),
                                  std::stof(i.properties["protection"]),
                                  std::stoi(i.properties["eqType"]),
                                  std::stoi(i.properties["materialType"])
                    ));
        if (i.subType == "aequipment")
            itemsList.push_back(
                    new ArtefactEquipment(level, i.imagePath, i.name, i.type, i.subType,
                                          i.rect.left, i.rect.top, i.rect.width, i.rect.height,
                                          i.layer,
                                          std::stoi(i.properties["state"]),
                                          std::stof(i.properties["protection"]),
                                          std::stoi(i.properties["eqType"]),
                                          std::stoi(i.properties["materialType"]),
                                          i.properties
                    ));
        if (i.subType == "aeweapon")
            itemsList.push_back(
                    new EnchantedArtefactWeapon(level, i.imagePath, i.name, i.type, i.subType,
                                                i.rect.left, i.rect.top, i.rect.width, i.rect.height,
                                                i.layer,
                                                std::stoi(i.properties["state"]),
                                                std::stof(i.properties["damage"]),
                                                i.properties
                    ));
        if (i.subType == "key")
            itemsList.push_back(
                    new Key(level, i.imagePath, i.name, i.type, i.subType,
                            i.rect.left, i.rect.top, i.rect.width, i.rect.height, i.layer,
                            std::stoi(i.properties["state"])));

    }

    for (auto i: itemsList) {
        if (i->state == Item::STATE::onMe) {
            if (dynamic_cast<Weapon *>(i) != nullptr) {
                p.weapon = dynamic_cast<Weapon *>(i);
            }
            if (dynamic_cast<Potion *>(i) != nullptr) {
                p.potions.emplace_back(dynamic_cast<Potion *>(i));
            }
            if (dynamic_cast<Equipment *>(i) != nullptr) {
                p.equipment[dynamic_cast<Equipment *>(i)->eqType] = dynamic_cast<Equipment *>(i);
            }
        }
        if (i->state == Item::STATE::inChest) {
            for (auto chest : chestsList) {
                if (chest->x == i->x && chest->y == i->y) {
                    chest->setItem(i);
                }
            }
        }
    }

    sf::Thread pThread([&p] {
        Clock clock, attackClock;
        while (window->isOpen()) {
            float time = clock.getElapsedTime().asMilliseconds();
            if (time > 50) {
                clock.restart();
                p.update(time);
            }
        }
    });

    pThread.launch();

    list<sf::Thread> threads;

    for (auto &it : enemiesList) {
        threads.emplace_back([&p, &level, it] {
            Clock clock, attackClock;
            while (window->isOpen()) {
                float time = clock.getElapsedTime().asMilliseconds();
                if (attackClock.getElapsedTime().asMilliseconds() > 100)
                    if (it->layer == level.currentLayer) {
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
                            it->dx = 0;
                            it->dy = 0;
                            it->acceptDamageFrom(&p);
                            p.acceptDamageFrom(it);
                            it->update(time);

                            if (it->health <= 0) {
                                p.changeSkillValue("lvl", it->lvl);
                                p.playerLevel = (int) p.getSkillValue("lvl") / 100;
                                return;
                            }

                            attackClock.restart();
                            clock.restart();
                        }
                    }
            }
        });
    }

    for (auto &th: threads)
        th.launch();

    while (window->isOpen()) {
        float time = clock.getElapsedTime().asMilliseconds();
        if (Keyboard::isKeyPressed(Keyboard::A)) p.key["A"] = true;
        if (Keyboard::isKeyPressed(Keyboard::D)) p.key["D"] = true;
        if (Keyboard::isKeyPressed(Keyboard::W)) p.key["W"] = true;
        if (Keyboard::isKeyPressed(Keyboard::S)) p.key["S"] = true;

        Event event{};
        if (time > 50) {
            clock.restart();

            while (window->pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window->close();
                if (ladderClock.getElapsedTime().asMilliseconds() > 60) {
                    ladderClock.restart();
                    if (p.STATE == Player::STATE::onladderup) {
                        level.goUp();
                        p.layer = 1;
                        p.STATE = Player::STATE::stay;
                        p.map = level.getAllStaticObjects();
                        for (auto enemy: enemiesList) {
                            enemy->map = level.getAllStaticObjects();;
                        }
                    }
                    if (p.STATE == Player::STATE::onladderdown) {
                        level.goDown();
                        p.layer = 0;
                        p.STATE = Player::STATE::stay;
                        p.map = level.getAllStaticObjects();
                        for (auto enemy: enemiesList) {
                            enemy->map = level.getAllStaticObjects();;
                        }
                    }
                }

                if (potionsClock.getElapsedTime().asMilliseconds() > 60) {
                    if (Keyboard::isKeyPressed(Keyboard::O)) {
                        potionsClock.restart();
                        if (p.currPotion == p.potions.size() - 1) {
                            p.currPotion = 0;
                            break;
                        } else {
                            p.currPotion++;
                            break;
                        }
                    }
                    if (Keyboard::isKeyPressed(Keyboard::P)) {
                        potionsClock.restart();
                        if (!p.potions.empty()) {
                            if (!p.potions[p.currPotion]->isUsingNow) {
                                p.potions[p.currPotion]->isUsingNow = true;
                                p.attributes[p.drinkPotion()[0].first] += p.drinkPotion()[0].second;
                            }
                        }
                    }

                }
            }

//            p.update(time);

            if (usingPotionClock.getElapsedTime().asSeconds() > 1) {
                for (auto potion: p.potions) {
                    if (potion->isUsingNow) {
                        potion->timer--;
                        if (potion->timer == 0) {
                            if (potion->changesListA[0].first != "hp") {
                                p.attributes[potion->changesListA[0].first] -= potion->changesListA[0].second;
                            }
                            p.deletePotion();
                        }
                    }
                }
                usingPotionClock.restart();
            }

            for (auto it = enemiesList.begin(); it != enemiesList.end(); it++) {
                if ((*it)->layer == level.currentLayer) {
                    Enemy *b = *it;
                    b->update(time);
                    if (!b->isAlive) {
                        it = enemiesList.erase(it);
                        delete b;
                    }
                }
            }

            if (doorClock.getElapsedTime().asMilliseconds() > 200) {
                for (auto b : doorsList) {
                    if (b->layer == level.currentLayer) {
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
            }

            if (chestClock.getElapsedTime().asMilliseconds() > 70) {
                for (auto b : chestsList) {
                    if (b->layer == level.currentLayer) {
                        if (p.getRect().intersects(b->getAreaRect())) {
                            if (Mouse::isButtonPressed(sf::Mouse::Left) && b->isLocked) {
                                if (b->open(p))
                                    chestSound.play();
                                chestClock.restart();
                            }
                        }
                        b->update(time);
                    }
                }
            }

            if (itemsClock.getElapsedTime().asMilliseconds() > 200)
                for (auto b : itemsList) {
                    if (b->layer == level.currentLayer) {
                        if (p.getRect().intersects(b->getRect()) && b->state == Item::STATE::onMap) {
                            if (Mouse::isButtonPressed(sf::Mouse::Left)) {
                                p.takeItem(b);
                                itemsClock.restart();
                            }
                        }
                        b->update(time);
                    }
                }

//            if (attackClock.getElapsedTime().asMilliseconds() > 100)
//                for (auto &it : enemiesList) {
//                    if (it->layer == level.currentLayer) {
//                        if (p.getRect().intersects(it->getRect())) {
//                            if (p.dx > 0) {
//                                it->dx = 0.1;
//                            }
//                            if (p.dx < 0) {
//                                it->dx = -0.1;
//                            }
//                            if (p.dy > 0) {
//                                it->dy = 0.1;
//                            }
//                            if (p.dy < 0) {
//                                it->dy = -0.1;
//                            }
//                            it->dx = 0;
//                            it->dy = 0;
//                            it->acceptDamageFrom(&p);
//                            p.acceptDamageFrom(it);
//
//                            if (it->health <= 0) {
//                                p.changeSkillValue("lvl", it->lvl);
//                                p.playerLevel = (int) p.getSkillValue("lvl") / 100;
//                            }
//
//                            it->update(time);
//                            attackClock.restart();
//                        }
//                    }
//                }
        }

        myView.viewMap(time);
        myView.changeView();
        window->setView(myView.view);
        window->clear(sf::Color(169, 169, 169));

        level.draw(*window);
        for (auto enemy : enemiesList) {
            if (enemy->layer == level.currentLayer)
                enemy->draw(*window);
        }
        for (auto door: doorsList) {
            if (door->layer == level.currentLayer)
                door->draw(*window);
        }
        for (auto chest: chestsList) {
            if (chest->layer == level.currentLayer)
                chest->draw(*window);
        }
        for (auto item: itemsList) {
            if (item->layer == level.currentLayer)
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