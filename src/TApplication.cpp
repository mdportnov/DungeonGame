#include <sstream>
#include <include/model/Level.h>
#include "iostream"
#include "include/TApplication.h"
#include "include/view.h"
#include "include/model/Player.h"

using namespace sf;

namespace MyGame {
    TApplication::TApplication() :
            window(nullptr) {
    }

    TApplication::~TApplication() = default;;

    void TApplication::Init() {
        window = new sf::RenderWindow(sf::VideoMode(640, 480), "DungeonGame");
        view.reset(sf::FloatRect(0, 0, 640, 480));
    }

    void TApplication::Run() {
        Clock clock;

        Level level;
        level.LoadFromFile("../res/level1.tmx");

        Player p(level, "temik_tiles.png", 50, 50, 30.0, 50.0);

//        Image map_image;
//        map_image.loadFromFile("../res/img/tileset_v2.png");
//        Texture map;
//        map.loadFromImage(map_image);
//        Sprite s_map;
//        s_map.setTexture(map);

        sf::RectangleShape textBG(sf::Vector2f(200, 40));
        textBG.setFillColor(Color::Black);

//        Font font;
//        font.loadFromFile("../res/font/karmafuture.ttf");
//        Text text("", font, 20);
//        text.setStyle(sf::Text::Bold | sf::Text::Underlined);

        while (window->isOpen()) {
            float time = clock.getElapsedTime().asMicroseconds();
            clock.restart();
            time = time / 800;

            sf::Event event;
            while (window->pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window->close();
            }

//            if (Keyboard::isKeyPressed(Keyboard::H)) {
//                sound.play();
//            }

            p.update(time);
            viewMap(time);
            changeView();
            window->setView(view);
            window->clear(sf::Color(169, 169, 169));

            level.Draw(*window);

//            for (int i = 0; i < HEIGHT_MAP; ++i) {
//                for (int j = 0; j < WIDTH_MAP; ++j) {
//                    if (TileMap[i][j] == ' ') s_map.setTextureRect(IntRect(0, 0, 50, 50));
//                    if (TileMap[i][j] == '0') s_map.setTextureRect(IntRect(100, 100, 50, 50));
//                    if (TileMap[i][j] == '[') s_map.setTextureRect(IntRect(0, 50, 50, 50));
//                    if (TileMap[i][j] == ']') s_map.setTextureRect(IntRect(100, 50, 50, 50));
//                    if (TileMap[i][j] == 'h') s_map.setTextureRect(IntRect(50, 50, 50, 50));
//                    s_map.setPosition(j * 50, i * 50);
//                    window->draw(s_map);
//                }
//            }
            window->draw(p.sprite);
//            std::ostringstream playerScoreString;
//            playerScoreString << p.playerScore;
//            text.setPosition(view.getCenter().x-300, view.getCenter().y-220);
//            text.setString("Hookah Score: "+playerScoreString.str());
//            textBG.setPosition(view.getCenter().x-310, view.getCenter().y-230);
//            window->draw(textBG);
//            window->draw(text);
            window->display();
        }
    }

    void TApplication::End() {
        if (window != nullptr) {
            delete window;
            window = nullptr;
        }
    }
}
