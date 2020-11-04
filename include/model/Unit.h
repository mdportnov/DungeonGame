#include "src/main.h"

using namespace sf;

class Unit : public ObjectOnField {
public:
    float x, y, dx, dy, speed, moveTimer = 0, playerScore, w, h, health;
    int dir;
    Texture texture;
    Sprite sprite;
    int framesCount = 0; // in sprite image
    double currentFrame = 0; // in sprite image
    Image image;
    bool isAlive;
    std::vector<Object> obj;//вектор объектов карты

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

    FloatRect getRect() {//ф-ция получения прямоугольника. его коорд,размеры (шир,высот).
        return FloatRect(x, y, w, h);//эта ф-ция нужна для проверки столкновений
    }

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
        checkCollision(0);

        y += dy * time;
        checkCollision(1);
        sprite.setPosition(x, y);

        speed = 0;

        if (health <= 0) {
            isAlive = false;
            speed = 0;
        }
    }

    void checkCollision(int num) {
        for (auto &i : obj)
            if (getRect().intersects(i.rect)) {
                if (i.name == "solid") {
                    if (dy > 0 && num == 1) {
                        y = i.rect.top - h;
                        dy = 0;
//                    STATE=stay;
                    }
                    if (dy < 0 && num == 1) {
                        y = i.rect.top + i.rect.height;
                        dy = 0;
                    }
                    if (dx > 0 && num == 0) { x = i.rect.left - w; }
                    if (dx < 0 && num == 0) { x = i.rect.left + i.rect.width; }
                }

                if (i.name == "ladder") {
//                    onLadder=true; if (STATE==climb) x=obj[i].rect.left-10;
                }
            }
    }
};