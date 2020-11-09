#include <sstream>
#include <include/model/Level.h>
#include "iostream"
#include "include/DungeonGameApp.h"
#include "include/model/View.h"
#include "include/model/Player.h"
#include "ObjectsParser.h"
#include <vector>
#include <list>
#include "include/model/Enemy.h"

using namespace sf;

namespace MyGame {
    DungeonGameApp::DungeonGameApp() :
            window(nullptr) {
    }

    DungeonGameApp::~DungeonGameApp() = default;;

    void DungeonGameApp::Init() {
        window = new sf::RenderWindow(sf::VideoMode(600, 400), "DungeonGame");
        view.reset(sf::FloatRect(0, 0, 600, 400));
    }

    void DungeonGameApp::Run() {
        Clock clock;

        Level level;
        level.loadMapFromFile("../res/level1.tmx");
        level.loadStateFromFile("../res/level1objects.xml");

        Object player = level.getPlayer();
        Player p(level, player.imagePath, player.name, player.rect.left, player.rect.top, player.rect.width,
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
            float time = clock.getElapsedTime().asMicroseconds();
            clock.restart();
            time = time / 800;

            sf::Event event;
            while (window->pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window->close();

                if (p.STATE == Player::onladderup) {
                    level.goUp();
                    p.STATE = Player::stay;
                    p.map = level.getAllMapObjects();
                }
                if (p.STATE == Player::onladderdown) {
                    level.goDown();
                    p.STATE = Player::stay;
                    p.map = level.getAllMapObjects();
                }
            }

            if (Keyboard::isKeyPressed(Keyboard::A)) p.key["A"] = true;
            if (Keyboard::isKeyPressed(Keyboard::D)) p.key["D"] = true;
            if (Keyboard::isKeyPressed(Keyboard::W)) p.key["W"] = true;
            if (Keyboard::isKeyPressed(Keyboard::S)) p.key["S"] = true;

            p.update(time);

            for (auto &it : e) {
                float offset = 20;
                if (it->getRect().intersects(p.getRect())) {
                    if (p.dx > 0) {
                        std::cout << "(*it)->x" << it->x << "\n";//враг
                        it->x = p.x + p.w + offset; //отталкиваем его от игрока вправо (впритык)
                        it->dx = 0;//останавливаем
                    }

                    if (p.dx < 0) {
                        it->x = p.x - it->w - offset; //отталкиваем его от игрока влево (впритык)
                        it->dx = 0; //останавливаем
                    }

                    if (p.dy > 0) {
                        it->y = p.y + p.h + offset;
                        it->dy = 0;
                    }

                    if (p.dy < 0) {
                        it->y = p.y - it->h - offset;
                        it->dy = 0;
                    }
                    it->update(time);
                    it->health-=30;
                }
            }

            for (auto it = e.begin(); it != e.end(); it++) {
                Enemy *b = *it;
                b->update(time);
                if (!b->isAlive) {
                    it = e.erase(it);
                    delete b;
                }
            }

            viewMap(time);
            changeView();
            window->setView(view);
            window->clear(sf::Color(169, 169, 169));

            level.draw(*window);

            window->draw(p.sprite);

            for (auto layerObjects : e) {
                window->draw(layerObjects->sprite);
            }

            window->display();
            ObjectsParser::saveToFileProgress(level, p, e);
        }
    }

    void DungeonGameApp::End() {
        if (window != nullptr) {
            delete window;
            window = nullptr;
        }
    }
}
