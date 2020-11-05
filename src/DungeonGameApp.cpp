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

        Object player = level.getObject("player");
        Player p(level, "temik_tiles.png", player.name, player.rect.left, player.rect.top, 30, 50);

        std::list<Enemy *> enemies;
        std::list<Enemy *>::iterator it;
        std::vector<Object> enemiesObj = level.getObjects("egorov");
        for (auto &i : enemiesObj) {
            enemies.push_back(
                    new Enemy(level, "leha_tiles.png", i.name, i.rect.left, i.rect.top, 30, 50));
        }

        while (window->isOpen()) {
            float time = clock.getElapsedTime().asMicroseconds();
            clock.restart();
            time = time / 800;

            sf::Event event;
            while (window->pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window->close();

                if (p.state == Unit::onladderup) {
                    level.goUp();
                    p.state = Unit::stay;
                    p.obj = level.getAllObjects();
                }
                if (p.state == Unit::onladderdown) {
                    level.goDown();
                    p.state = Unit::stay;
                    p.obj = level.getAllObjects();
                }
            }


            p.update(time);

            for (it = enemies.begin(); it != enemies.end(); it++) {
                Enemy *b = *it;
                b->update(time);
                if (!b->isAlive) {
                    it = enemies.erase(it);
                    delete b;
                }
            }

            viewMap(time);
            changeView();
            window->setView(view);
//            window->clear(sf::Color(169, 169, 169));

            level.draw(*window);

            window->draw(p.sprite);

            for (auto enemy : enemies) {
                window->draw(enemy->sprite);
            }
            window->display();
            ObjectsParser::saveToFileProgress(level, p, enemies);

        }
    }

    void DungeonGameApp::End() {
        if (window != nullptr) {
            delete window;
            window = nullptr;
        }
    }
}
