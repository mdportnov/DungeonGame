#include "include/model/Player.h"

Player::Player(Level &level, MyView &view, std::string fileName, std::string name, float x, float y, float w, float h)
        : Unit(level, fileName, name, x, y, w, h) {
    framesCount = 5;
    speed = 0.1;
    this->view = &view;
}

void Player::update(float time) {
    control(time);
    keyboard();
    Unit::update(time);
}

void Player::keyboard() {
    if (key["A"]) {
        dx = -speed;
        dy = 0;
        if (STATE == STATE::stay) STATE = STATE::walk;
    }

    if (key["D"]) {
        dx = speed;
        dy = 0;
        if (STATE == STATE::stay) STATE = STATE::walk;
    }

    if (key["W"]) {
        dx = 0;
        dy = -speed;
    }

    if (key["S"]) {
        dx = 0;
        dy = speed;
    }

    if (!(key["D"] || key["A"])) {
        dx = 0;
        if (STATE == STATE::walk) STATE = STATE::stay;
    }

    if (!(key["W"] || key["S"])) {
        dy = 0;
        if (STATE == STATE::walk) STATE = STATE::stay;
    }

    key["A"] = key["S"] = key["W"] = key["D"] = key["Space"] = false;

}

void Player::control(float time) {
    if (key["A"]) {
        sprite.setOrigin({30, 0});
        sprite.setScale({-1, 1});

        currentFrame += 0.005 * time;
        if (currentFrame > framesCount) currentFrame -= framesCount;
        sprite.setTextureRect(IntRect(30 * int(currentFrame), 0, 30, 50));
        view->getPlayerCoordinateForView(this->getX(), this->getY());
    }

    if (key["D"]) {
        sprite.setScale({1, 1});
        sprite.setOrigin({0, 0});

        currentFrame += 0.005 * time;
        if (currentFrame > framesCount) currentFrame -= framesCount;
        sprite.setTextureRect(IntRect(30 * int(currentFrame), 0, 30, 50));
        view->getPlayerCoordinateForView(this->getX(), this->getY());
    }

    if (key["W"]) {
        currentFrame += 0.005 * time;
        if (currentFrame > framesCount) currentFrame -= framesCount;
        sprite.setTextureRect(IntRect(30 * int(currentFrame), 0, 30, 50));
        view->getPlayerCoordinateForView(this->getX(), this->getY());
    }

    if (key["S"]) {
        currentFrame += 0.005 * time;
        if (currentFrame > framesCount) currentFrame -= framesCount;
        sprite.setTextureRect(IntRect(30 * int(currentFrame), 0, 30, 50));
        view->getPlayerCoordinateForView(this->getX(), this->getY());
    }
}

void Player::checkCollision(int num) {
    Unit::checkCollision(num);
    for (auto &i : map)
        if (getRect().intersects(i.rect)) {
            if (i.name == "ladder_up" &&
                Mouse::isButtonPressed(sf::Mouse::Left)
                    ) {
                STATE = STATE::onladderup;
            }
            if (i.name == "ladder_down" &&
                Mouse::isButtonPressed(sf::Mouse::Left)
                    ) {
                STATE = STATE::onladderdown;
            }
        }

//        for (it = objects.begin(); it != objects.end(); ++it)
//            if (getRect().intersects(it->rect)) {
//                if (it->name == "python") {
//                    level.deleteObject(it);
//                    objects=level.getAllObjects();
//                }
//            }
}

void Player::takeItem(Item &item) {
    if (item.subType == "weapon") {
        weapon = new Weapon(item.name);
    }

    if (item.subType == "potion") {
//        drinkPotion(Potion());
    }
}

