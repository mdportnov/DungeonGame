#include "include/model/InfoBar.h"

void InfoBar::draw(RenderWindow &window) {
    Vector2f center = window.getView().getCenter();
    Vector2f size = window.getView().getSize();

    float barOriginX = center.x - size.x / 2 + 10;
    float barOriginY = center.y + size.y / 2 - 40;

    charsBar.setPosition(barOriginX, barOriginY);
    charsBar.setSize({size.x - 20, 30});
    charsBar.setOutlineColor(Color::Red);
    charsBar.setOutlineThickness(2);

    window.draw(charsBar);
    barOriginX += 10;

    for (auto ch: player->attributes) {
        Text text;
        text.setFont(font);
        text.setPosition(barOriginX, barOriginY + 2);
        text.setString(ch.first + ": " + to_string(ch.second));
        text.setCharacterSize(16);
        text.setFillColor(Color::Black);
        window.draw(text);
        barOriginX += 80;
    }

    float itemsBarOriginX = center.x - size.x / 2 + 10;
    float itemsBarOriginY = center.y - 40;

    itemsBar.setPosition(itemsBarOriginX, itemsBarOriginY);
    itemsBar.setSize({30, 180});
    itemsBar.setOutlineColor(Color::Red);
    itemsBar.setOutlineThickness(2);
    window.draw(itemsBar);

    if (player->weapon != nullptr) {
        player->weapon->sprite.setScale(0.7, 0.7);
        player->weapon->sprite.setPosition(itemsBarOriginX + 10, itemsBarOriginY + 20);
        Texture texture;
        Image image;
        image.loadFromFile("../res/img/items/weapon_axe.png");
        texture.loadFromImage(image);
        player->weapon->sprite.setTexture(texture);
        player->weapon->sprite.setTextureRect(IntRect(0, 0, 50, 50));
//        window.draw(player->weapon->sprite);
    }
//    if (player->potions[0] != nullptr) {
//        player->potions[0]->sprite.setScale(0.7, 0.7);
//        player->potions[0]->sprite.setPosition(itemsBarOriginX + 10, itemsBarOriginY + 20);
//        Texture texture;
//        Image image;
//        image.loadFromFile("../res/img/items/weapon_axe.png");
//        texture.loadFromImage(image);
//        player->potions[0]->sprite.setTexture(texture);
//        player->potions[0]->sprite.setTextureRect(IntRect(0, 0, 50, 50));
//        window.draw(player->potions[0]->sprite);
//    }

}

InfoBar::InfoBar() {
    if (!font.loadFromFile("../res/font/karmafuture.ttf"))
        cout << "Font cannot be downloaded";
//    image.loadFromFile("../res/img/life.png");
//    image.createMaskFromColor(Color(50, 96, 166));
//    t.loadFromImage(image);
//    s.setTexture(t);
//    s.setTextureRect(IntRect(783, 2, 15, 84));
}

void InfoBar::observe(Player *p) {
    this->player = p;
}
