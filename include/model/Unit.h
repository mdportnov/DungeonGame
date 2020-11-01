#include "main.h"
#include "include/map.h"

using namespace sf;

class Unit : public ObjectOnField {
public:
    float x, y, dx, dy, speed, moveTimer, playerScore, w, h, health;
    int dir;
    Texture texture;
    Sprite sprite;
    int framesCount; // in sprite image
    double currentFrame; // in sprite image
    String fileName;
    Image image;
    bool isAlive;

    Unit(const String& fileName, float x, float y, float w, float h) {
        health = 100;
        isAlive = true;
        playerScore = 0;
        dx = 0;
        dy = 0;
        speed = 0;
        dir = 0;
        this->fileName = fileName;
        this->w = w;
        this->h = h;
        image.loadFromFile("../res/img/" + this->fileName);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        this->x = x;
        this->y = y;
        sprite.setTextureRect(IntRect(0, 0, w, h));
    }

    float getX() const {
        return x;
    }

    float getY() const {
        return y;
    }

    void acceptDamage(Unit from);

    void makeDamage(Unit to);

    virtual void update(float time) {
        switch (dir) {
            case 0:
                dx = speed;
                dy = 0;
                break;
            case 1:
                dx = -speed;
                dy = 0;
                break;
            case 2:
                dx = 0;
                dy = speed;
                break;
            case 3:
                dx = 0;
                dy = -speed;
                break;
        }
        x += dx * time;
        y += dy * time;
        speed = 0;
        sprite.setPosition(x, y);

        if (health <= 0) {
            isAlive = false;
            speed = 0;
        }

        interactionWithMap(TileMap);
    }

    void interactionWithMap(sf::String map[]) {
        float tileSize = 50;

        for (int i = y / tileSize; i < (y + h) /
                                       tileSize; i++)
            for (int j = x / tileSize; j < (x + w) / tileSize; j++)
            {
                if (map[i][j] == '0')
                {
                    if (dy > 0) y = i * tileSize - h;
                    if (dy < 0) y = i * tileSize + tileSize;
                    if (dx > 0) x = j * tileSize - w;
                    if (dx < 0) x = j * tileSize + tileSize;
                }
                if (map[i][j] == ']') {
                    x = 11 * 50;
                    y = 5 * 50;
                }
                if (map[i][j] == '[') {
                    x = 3 * 50;
                    y = 2 * 50;
                }
                if (map[i][j] == 'h') {
                    map[i][j] = ' ';
                    playerScore++;
                }
            }
    }
};