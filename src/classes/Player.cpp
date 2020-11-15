#include <include/model/equip/Key.h>
#include <include/model/Door.h>

#include <utility>
#include <random>
#include "include/model/Player.h"

Player::Player(Level &level, MyView &view, std::string fileName, std::string name, float x, float y, float w, float h)
        : Unit(level, fileName, name, x, y, w, h) {
    framesCount = 5;
    speed = 0.1;
    this->view = &view;
    bunchOfKeys = BunchOfKeys();
}

void Player::update(float time) {
    speed = attributes["sp"];
    control(time);
    keyboard();
    Unit::update(time);
}

void Player::keyboard() {
    if (key["A"]) {
        dx = -speed;
        dy = 0;
    }

    if (key["D"]) {
        dx = speed;
        dy = 0;
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
    }

    if (!(key["W"] || key["S"])) {
        dy = 0;
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
            if (Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (i.name == "ladder_up") {
                    STATE = STATE::onladderup;
                }
                if (i.name == "ladder_down") {
                    STATE = STATE::onladderdown;
                }
            }
        }
}

void Player::takeItem(Item *item) {
    if (dynamic_cast<Weapon *>(item) != nullptr) {
        if (weapon == nullptr) {
            weapon = dynamic_cast<Weapon *>(item);
            dynamic_cast<Weapon *>(item)->state = Item::STATE::onMe;
        } else {
            if (dynamic_cast<Weapon *>(item)->getDamage() > weapon->getDamage()) {
                weapon = dynamic_cast<Weapon *>(item);
                dynamic_cast<Weapon *>(item)->state = Item::STATE::onMe;
            } else
                dynamic_cast<Weapon *>(item)->state = Item::STATE::nowhere;
        }
    }

    if (dynamic_cast<Potion *>(item) != nullptr) {
        if (potions.size() < 4) {
            item->state = Item::STATE::onMe;
            potions.push_back(dynamic_cast<Potion *>(item));
            currentPotion = (int) potions.size() - 1;
        }
    }
    if (dynamic_cast<Equipment *>(item) != nullptr) {
        auto *equip = dynamic_cast<Equipment *>(item);

        if (equipment[equip->eqType] == nullptr) {
            dynamic_cast<Equipment *>(item)->state = Item::STATE::onMe;
            equipment[equip->eqType] = equip;
        } else {
            if (dynamic_cast<Equipment *>(item)->protection > equipment[equip->eqType]->protection) {
                equipment[equip->eqType] = dynamic_cast<Equipment *>(item);
                dynamic_cast<Equipment *>(item)->state = Item::STATE::onMe;
            } else
                dynamic_cast<Equipment *>(item)->state = Item::STATE::nowhere;
        }
    }

    if (dynamic_cast<Key *>(item) != nullptr) {
        bunchOfKeys.addNewOne();
        dynamic_cast<Key *>(item)->state = Item::STATE::nowhere;
    }
}

vector<pair<string, float>> Player::drinkPotion() {
    vector<pair<string, float>> changesList;
    if (!potions.empty()) {
        changesList = (*(potions.begin() + currentPotion))->changesList;
    }
    return changesList;
}

void Player::deletePotion() {
    if (!potions.empty()) {
        (*(potions.begin() + currentPotion))->state = Item::STATE::nowhere;
        potions.erase(potions.begin() + currentPotion);
        currentPotion = 0;
    }
}

void Player::init(std::map<string, float> t) {
    this->attributes = std::move(t);
}

void Player::acceptDamageFrom(Unit &unit) {
    if (isHit(attributes["dx"]))
        attributes["hp"] -= calculateProtection() + unit.calculateDamage();
}


void Player::draw(RenderWindow &window) {
    Unit::draw(window);
    if (weapon != nullptr) {
        weapon->sprite.setScale(-0.6, 0.6);
        weapon->sprite.setPosition(x + 40, y + 10);
        window.draw(weapon->sprite);
    }
}

float Player::calculateProtection() {
    float protection = 0;
    for (auto &equip : equipment) {
        if (equip != nullptr) {
            protection += equip->protection;
        }
    }
    protection += attributes["st"];
    return protection;
}

bool Player::isHit(double prob) {
    std::mt19937 rand_engine(std::random_device{}());
    std::bernoulli_distribution d(prob);
    return d(rand_engine);
}

