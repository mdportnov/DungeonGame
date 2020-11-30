#include "include/model/ObjectOnField.h"

ObjectOnField::ObjectOnField(Level &level, string &fileName, string &name, float x, float y, float w, float h, int layer) {
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->level = level;
    this->layer = layer;
    this->name = name;
    this->image.loadFromFile("../res/img/" + fileName);
    texture.loadFromImage(image);
    sprite.setTexture(texture);
    sprite.setTextureRect(IntRect(0, 0, w, h));
    if (!font.loadFromFile("../res/font/karmafuture.ttf"))
        cout << "Font cannot be downloaded";
}

void ObjectOnField::update(float time) {
    sprite.setPosition(x, y);
}

void ObjectOnField::draw(RenderWindow &window) {
    window.draw(sprite);
}

