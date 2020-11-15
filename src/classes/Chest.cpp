#include <random>
#include "include/model/Chest.h"

Chest::Chest(Level &level, string &fileName, string &name,
             float x, float y, float w, float h, int lockLevel, bool isLocked) : ObjectOnField(level, fileName, name, x,
                                                                                               y, w, h) {
    this->lockLevel = lockLevel;
    this->isLocked = isLocked;
    if (!isLocked) {
        this->image.loadFromFile("../res/img/chest_opened.png");
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setTextureRect(IntRect(0, 0, w, h));
        storedItem = nullptr;
    }
}

FloatRect Chest::getAreaRect() {
    return {x - 50, y - 50, w + 100, h + 100};
}

bool Chest::open(Player &player) {
    if (player.bunchOfKeys.getSize() != 0) {
        if (canOpen(getProbabilityOfOpen(player))) {
            this->image.loadFromFile("../res/img/chest_opened.png");
            texture.loadFromImage(image);
            sprite.setTexture(texture);
            sprite.setTextureRect(IntRect(0, 0, w, h));
            storedItem->state = Item::STATE::onMap;
            isLocked = false;
            return true;
        }
    }
    player.bunchOfKeys.brokeKey();
    return false;
}

void Chest::setItem(Item *item) {
    storedItem = item;
}

float Chest::getProbabilityOfOpen(Player &player) {
    float prob = player.attributes["dx"] / 100 + player.attributes["st"] / 100 + player.attributes["lvl"] / 100;
    cout << prob << endl;
    return prob;
}

bool Chest::canOpen(double prob) {
    std::mt19937 rand_engine(std::random_device{}());
    std::bernoulli_distribution d(prob);
    return d(rand_engine);
}
