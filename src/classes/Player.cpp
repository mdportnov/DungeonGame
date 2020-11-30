#include <include/model/equip/Key.h>
#include <include/model/Door.h>

#include <utility>
#include <random>
#include <include/model/equip/ArtefactEquipment.h>
#include <include/model/equip/ArtefactWeapon.h>
#include <include/model/equip/EnchantedWeapon.h>
#include "include/model/Player.h"

Player::Player(Level &level, MyView &view, string fileName, string name, float x, float y, float w, float h, int layer,
               std::map<string, string> props)
        : Unit(level, fileName, name, x, y, w, h, layer) {
    this->view = &view;
    for (auto &a: props) {
        attributes.insert(a.first, std::stof(a.second));
    }
    framesCount = 5;

    speed = getSkillValue("sp");
    bunchOfKeys = BunchOfKeys();

    attributesDiff.insert("mxhp", 20);
    attributesDiff.insert("xp", 20);
    attributesDiff.insert("sp", 0.01);
    attributesDiff.insert("pw", 3);
    attributesDiff.insert("st", 0.05);
    attributesDiff.insert("dx", 0.05);
    attributesDiff.insert("lvl", 0);
    attributesDiff.insert("hp", 0);

    playerLevel = (int) getSkillValue("lvl") / 100;
}

void Player::update(float time) {
    speed = getSkillValue("sp");
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

void Player::takeItem(Item *&item) {
    if (dynamic_cast<Weapon *>(item) != nullptr) {
        dynamic_cast<Weapon *>(item)->state = Item::STATE::onMe;

        if (dynamic_cast<ArtefactWeapon *>(weapon) != nullptr) {
            for (const auto &prop: dynamic_cast<ArtefactWeapon *>(weapon)->changesListA) {
                attributes[prop.first] -= prop.second;
            }
        }

        if (dynamic_cast<ArtefactWeapon *>(item) != nullptr) {
            for (const auto &prop: dynamic_cast<ArtefactWeapon *>(item)->changesListA) {
                attributes[prop.first] += prop.second;
            }
        }

        if (weapon != nullptr) {
            weapon->sprite.setScale(1.0, 1.0);
            weapon->x = x - 10;
            weapon->y = y - 50;
            weapon->state = Item::STATE::onMap;
        }

        weapon = dynamic_cast<Weapon *>(item);
    }

    if (dynamic_cast<Potion *>(item) != nullptr) {
        if (potions.size() < 4) {
            item->state = Item::STATE::onMe;
            potions.push_back(dynamic_cast<Potion *>(item));
            currPotion = (int) potions.size() - 1;
        }
    }

    if (dynamic_cast<Equipment *>(item) != nullptr) {
        auto *equip = dynamic_cast<Equipment *>(item);
        equip->state = Item::STATE::onMe;

        if (dynamic_cast<ArtefactEquipment *>(equipment[equip->eqType]) != nullptr) {
            for (const auto &prop: dynamic_cast<ArtefactEquipment *>(equipment[equip->eqType])->changesListA) {
                attributes[prop.first] -= prop.second;
            }
        }

        if (dynamic_cast<ArtefactEquipment *>(equip) != nullptr) {
            for (const auto &prop: dynamic_cast<ArtefactEquipment *>(item)->changesListA) {
                attributes[prop.first] += prop.second;
            }
        }

        if (equipment[equip->eqType] != nullptr) {
            equipment[equip->eqType]->sprite.setScale(1.0, 1.0);
            equipment[equip->eqType]->x = x - 50;
            equipment[equip->eqType]->y = y;
            equipment[equip->eqType]->state = Item::STATE::onMap;
        }

        equipment[equip->eqType] = dynamic_cast<Equipment *>(item);

    }

    if (dynamic_cast<Key *>(item) != nullptr) {
        bunchOfKeys.addNewOne();
        dynamic_cast<Key *>(item)->state = Item::STATE::nowhere;
    }
}

vector<pair<string, float>> Player::drinkPotion() {
    vector<pair<string, float>> changesList;
    if (!potions.empty()) {
        changesList = (*(potions.begin() + currPotion))->changesListA;
    }
    return changesList;
}

void Player::deletePotion() {
    int index = 0;
    for (auto potion: potions) {
        if (potion->timer == 0) {
            potions.erase(potions.begin() + index);
            currPotion = 0;
        }
        index++;
    }
}

void Player::acceptDamageFrom(Unit *unit) {
    if (isHit(getSkillValue("dx")))
        changeSkillValue("hp", -(1 - calculateProtection() / 120) * unit->calculateDamage(this));
}

float Player::calculateProtection() {
    float protection = 0;
    for (auto equip : equipment) {
        if (equip != nullptr) {
            protection += equip->protection;
        }
    }
    protection += getSkillValue("st");
    return protection;
}

float Player::calculateDamage(Unit *unit) {
    if (weapon != nullptr) {
        auto *enchantedWeapon = dynamic_cast<EnchantedWeapon *>(weapon);
        if (enchantedWeapon != nullptr) {
            return getSkillValue("pw") * getSkillValue("st") +
                   enchantedWeapon->calculateDamage(unit->name);
        }
        return getSkillValue("pw") * getSkillValue("st") + weapon->calculateDamage();
    } else
        return getSkillValue("pw") * getSkillValue("st");
}

void Player::draw(RenderWindow &window) {
    Unit::draw(window);
    if (weapon != nullptr) {
        weapon->sprite.setScale(-0.6, 0.6);
        weapon->sprite.setPosition(x + 40, y + 10);
        window.draw(weapon->sprite);
    }
}

bool Player::isHit(double prob) {
    std::mt19937 rand_engine(std::random_device{}());
    std::bernoulli_distribution d(prob);
    return d(rand_engine);
}

float Player::getSkillValue(const string &shortname) {
//    return attributes[shortname];
    return attributes[shortname] + (float) playerLevel * attributesDiff[shortname];
}

void Player::changeSkillValue(const string &shortname, float diff) {
    attributes[shortname] += diff;
}

