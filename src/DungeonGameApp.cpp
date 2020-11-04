#include <sstream>
#include <include/model/Level.h>
#include "iostream"
#include "include/DungeonGameApp.h"
#include "include/model/View.h"
#include "include/model/Player.h"
#include <vector>
#include <list>
#include <include/model/Enemy.h>

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
        level.loadFromFile("../res/level1.tmx");

        Object egorov = level.getObject("egorov");

        Player p(level, "temik_tiles.png", 100, 50, 30.0, 50.0);
        Enemy enemy(level, "leha_tiles.png", egorov.rect.left, egorov.rect.top, 30, 50);

//        std::list<Unit *> units;
//        std::list<Unit *>::iterator it;
//        std::vector<Object> enemies = level.getObjects("egorov");

//        for (int i = 0; i < enemies.size(); i++)
//            enemies.push_back(new Enemy(level, "leha_tiles.png", enemies[i].rect.left, enemies[i].rect.top, 200, 97));


        while (window->isOpen()) {
//            window->setKeyRepeatEnabled(false);

            float time = clock.getElapsedTime().asMicroseconds();
            clock.restart();
            time = time / 800;

            sf::Event event;
            while (window->pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window->close();
            }

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

            p.update(time);

            enemy.update(time);

            viewMap(time);
            changeView();
            window->setView(view);
            window->clear(sf::Color(169, 169, 169));

            level.draw(*window);

            window->draw(p.sprite);
            window->draw(enemy.sprite);
            window->display();
        }
    }

    void DungeonGameApp::End() {
        if (window != nullptr) {
            delete window;
            window = nullptr;
        }
    }
}
