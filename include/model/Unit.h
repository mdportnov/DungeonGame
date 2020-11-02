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
    std::vector<Object> obj;//вектор объектов карты

//    Unit(const String& fileName, float x, float y, float w, float h) {
    Unit(Level level, std::string fileName, float x, float y, float w, float h) {
        health = 100;
        isAlive = true;
        playerScore = 0;
        dx = 0;
        dy = 0;
        speed = 0;
        dir = 0;
        this->w = w;
        this->h = h;
        this->image.loadFromFile("../res/img/" + fileName);
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
        checkCollisionWithMap(dx, 0);

        y += dy * time;
        checkCollisionWithMap(0, dy);

        speed = 0;
        sprite.setPosition(x, y);

        if (health <= 0) {
            isAlive = false;
            speed = 0;
        }
//        interactionWithMap(Level);
    }

    FloatRect getRect() {//ф-ция получения прямоугольника. его коорд,размеры (шир,высот).
        return FloatRect(x, y, w, h);//эта ф-ция нужна для проверки столкновений
    }

    void interactionWithMap(sf::String map[]) {
//        float tileSize = 50;
//        for (int i = y / tileSize; i < (y + h) /
//                                       tileSize; i++)
//            for (int j = x / tileSize; j < (x + w) / tileSize; j++) {
//                if (map[i][j] == '0') {
//                    if (dy > 0) y = i * tileSize - h;
//                    if (dy < 0) y = i * tileSize + tileSize;
//                    if (dx > 0) x = j * tileSize - w;
//                    if (dx < 0) x = j * tileSize + tileSize;
//                }
//                if (map[i][j] == ']') {
//                    x = 11 * 50;
//                    y = 5 * 50;
//                }
//                if (map[i][j] == '[') {
//                    x = 3 * 50;
//                    y = 2 * 50;
//                }
//                if (map[i][j] == 'h') {
//                    map[i][j] = ' ';
//                    playerScore++;
//                }
//            }

        for (int i = 0; i < obj.size(); i++)//проходимся по объектам
            if (getRect().intersects(obj[i].rect))//проверяем пересечение игрока с объектом
            {
                if (obj[i].name == "solid")//если встретили препятствие
                {
                    if (dy > 0) {
                        y = obj[i].rect.top - h;
                        dy = 0;
                    }
                    if (dy < 0) {
                        y = obj[i].rect.top + obj[i].rect.height;
                        dy = 0;
                    }
                    if (dx > 0) { x = obj[i].rect.left - w; }
                    if (dx < 0) { x = obj[i].rect.left + obj[i].rect.width; }
                }
            }
    }

    void checkCollisionWithMap(float Dx, float Dy) {
        for (int i = 0; i < obj.size(); i++)//проходимся по объектам
            if (getRect().intersects(obj[i].rect))//проверяем пересечение игрока с объектом
            {
                if (obj[i].name == "9")//если встретили препятствие
                {
                    if (Dy > 0) {
                        y = obj[i].rect.top - h;
                        dy = 0;
                    }
                    if (Dy < 0) {
                        y = obj[i].rect.top + obj[i].rect.height;
                        dy = 0;
                    }
                    if (Dx > 0) { x = obj[i].rect.left - w; }
                    if (Dx < 0) { x = obj[i].rect.left + obj[i].rect.width; }
                }
            }
    }
};