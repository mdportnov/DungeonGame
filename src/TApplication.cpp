#include "include/TApplication.h"
#include "iostream"

using namespace sf;

namespace MyGame {
    TApplication::TApplication() :
            window(nullptr) {
    }

    TApplication::~TApplication() = default;;

    void TApplication::Init() {
        window = new sf::RenderWindow(sf::VideoMode(640, 640), "DungeonGame");
    }

    void TApplication::Run() {
        Clock clock;
        float CurrentFrame=0;

        Texture texture;
        texture.loadFromFile("../img/leha_tiles.png");

        Sprite sprite;
        sprite.setTexture(texture);
        sprite.setTextureRect(IntRect(0, 0, 30, 50));
        sprite.setScale(2.0, 2.0);
        sprite.setPosition(50, 25);

        while (window->isOpen()) {
            float time = clock.getElapsedTime().asMicroseconds();
            clock.restart();
            time = time / 800;

            sf::Event event;
            while (window->pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window->close();
            }

            if (Keyboard::isKeyPressed(Keyboard::Left)) {
                CurrentFrame+=0.005*time;
                if(CurrentFrame>4) CurrentFrame-=4;
                sprite.setTextureRect(IntRect(30*int(CurrentFrame), 0, 30, 50));
                sprite.setScale(-2, 2);
                sprite.move(-0.1*time, 0);
            }
            if (Keyboard::isKeyPressed(Keyboard::Right)) {
                CurrentFrame+=0.005*time;
                if(CurrentFrame>4) CurrentFrame-=4;
                sprite.setTextureRect(IntRect(30*int(CurrentFrame), 0, 30, 50));
                sprite.setScale(2, 2);
                sprite.move(0.1*time, 0);
            }
            if (Keyboard::isKeyPressed(Keyboard::Up)) {
                sprite.move(0, -0.1*time);
            }
            if (Keyboard::isKeyPressed(Keyboard::Down)) {
                sprite.move(0, 0.1*time);
            }

            window->clear(sf::Color::Black);
            window->draw(sprite);
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
