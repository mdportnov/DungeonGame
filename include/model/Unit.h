#include "../main.h"

#pragma once

using namespace sf;

class Unit : public ObjectOnField {
public:
    float dx, dy, speed, health;
    int framesCount = 0; // in sprite image
    double currentFrame = 0; // in sprite image
    Image image;
    bool isAlive;
    std::vector<Object> map; //вектор тайлов карты

    std::string name;

    Unit(Level &level, std::string &fileName,
         std::string &name, float x, float y, float w, float h) : ObjectOnField(x, y, w, h, level) {
        this->level = level;
        this->map = level.getAllMapObjects();
        this->name = name;
        this->image.loadFromFile("../res/img/" + fileName);

        isAlive = true;
        health = 100;

        dx = 0;
        dy = 0;
        speed = 0;
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setTextureRect(IntRect(0, 0, w, h));
    }

    Unit(Level &level, Sprite &sprite,
         std::string &name, float x, float y, float w, float h) : ObjectOnField(x, y, w, h, level) {
        this->sprite = sprite;
        this->name = name;
        this->w = w;
        this->h = h;
        this->x = x;
        this->y = y;
        this->level = level;
        this->map = level.getAllMapObjects();

        isAlive = true;
        health = 100;

        dx = 0;
        dy = 0;
        speed = 0;
    }

    void init(std::string name, float speed = 0, int health = 100) {
        this->name = name;
        this->speed = speed;
        this->health = health;
    }

    float getX() const {
        return x;
    }

    float getY() const {
        return y;
    }

    FloatRect getRect() {//ф-ция получения прямоугольника. его коорд,размеры (шир,высот).
        return FloatRect(x, y, w, h);//эта ф-ция нужна для проверки столкновений
    }

    virtual void update(float time) {
//        switch (state) {
//            case right:
//                dx = speed;
//                dy = 0;
//                break;
//            case left:
//                dx = -speed;
//                dy = 0;
//                break;
//            case down:
//                dx = 0;
//                dy = speed;
//                break;
//            case up:
//                dx = 0;
//                dy = -speed;
//                break;
//            case stay:
//                break;
//        }
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

    virtual void checkCollision(int num) {
        for (auto &i : map)
            if (getRect().intersects(i.rect)) {
                if (i.name == "solid") {
                    if (dy > 0 && num == 1) {
                        y = i.rect.top - h;
                        dy = 0;
                    }
                    if (dy < 0 && num == 1) {
                        y = i.rect.top + i.rect.height;
                        dy = 0;
                    }
                    if (dx > 0 && num == 0) { x = i.rect.left - w; }
                    if (dx < 0 && num == 0) { x = i.rect.left + i.rect.width; }
                }
            }
    }

    void acceptDamage(Unit from);

    void makeDamage(Unit to);
};