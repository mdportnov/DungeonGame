#include <sstream>

#pragma once

#include <include/model/Level.h>
#include "iostream"
#include "include/DungeonGameApp.h"
#include "include/model/MyView.h"
#include "include/model/Player.h"
#include "include/model/ObjectsParser.h"
#include <vector>
#include <list>
#include "include/model/Enemy.h"

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
        Clock clock;

        Level level;
        level.loadMapFromFile("../res/level1.tmx");
        level.loadStateFromFile("../res/level1objects.xml");

        Object player = level.getPlayer();
        Player p(level, myView, player.imagePath, player.name, player.rect.left, player.rect.top, player.rect.width,
                 player.rect.height);

        std::vector<Object> enemiesObjects = level.getEnemies();
        std::list<Enemy *> e;
        std::list<Enemy *>::iterator enemy_it;

        std::vector<Object> itemsObjects = level.getItems();
        std::list<Item *> itemsList;
        std::list<Item *>::iterator item_it;

        for (auto &i : enemiesObjects) {
            e.push_back(new Enemy(level, i.imagePath, i.name, i.rect.left, i.rect.top, i.rect.width, i.rect.height));
        }

//        for (auto &i : itemsObjects) {
//            itemsList.push_back(
//                    new Item(level, i.imagePath, i.name, i.rect.left, i.rect.top, i.rect.width, i.rect.height));
//        }

        while (window->isOpen()) {
            float time = clock.getElapsedTime().asMilliseconds();
            if (Keyboard::isKeyPressed(Keyboard::A)) p.key["A"] = true;
            if (Keyboard::isKeyPressed(Keyboard::D)) p.key["D"] = true;
            if (Keyboard::isKeyPressed(Keyboard::W)) p.key["W"] = true;
            if (Keyboard::isKeyPressed(Keyboard::S)) p.key["S"] = true;

            Event event;
            bool ladderUsed = false;
            if (time > 50) {
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
                }
                p.update(time);

                for (auto it = e.begin(); it != e.end(); it++) {
                    Enemy *b = *it;
                    b->update(time);
                    if (!b->isAlive) {
                        it = e.erase(it);
                        delete b;
                    }
                }

                for (auto &it : e) {
                    float offset = 20;

                    if (p.getRect().intersects(it->getRect())) {
                        if (p.dx > 0) {
                            it->x = p.x + p.w + offset; //отталкиваем его от игрока вправо
                            it->dx = 0.1;
                        }

                        if (p.dx < 0) {
                            it->x = p.x - it->w - offset; //отталкиваем его от игрока влево
                            it->dx = -0.1;
                        }

                        if (p.dy > 0) {
                            it->y = p.y + p.h + offset;
                            it->dy = 0.1;
                        }

                        if (p.dy < 0) {
                            it->y = p.y - it->h - offset;
                            it->dy = -0.1;
                        }
                        it->update(time);
                        it->dx = 0;
                        it->dy = 0;
//                        it->health -= 30;
                    }
                }
            }

            myView.viewMap(time);
            myView.changeView();
            window->setView(myView.view);
            window->clear(sf::Color(169, 169, 169));

            level.draw(*window);

            window->draw(p.sprite);

            for (auto enemy : e) {
                if ((*enemy).name == "egorov") {
                    RectangleShape rect(Vector2f(enemy->getEnemyArea().width, enemy->getEnemyArea().height));
                    rect.setPosition(enemy->x - enemy->getEnemyArea().width / 2 + enemy->w / 2,
                                     enemy->y - enemy->getEnemyArea().height / 2 + enemy->h / 2);
                    rect.setOutlineThickness(5);
                    rect.setFillColor(Color::Transparent);
                    rect.setOutlineColor(sf::Color(250, 150, 100));
                    window->draw(rect);
                }
                window->draw(enemy->sprite);
            }
            window->display();
//            ObjectsParser::saveToFileProgress(level, p, e);
        }
    }

    void DungeonGameApp::End() {
        if (window != nullptr) {
            delete window;
            window = nullptr;
        }
    }
}
