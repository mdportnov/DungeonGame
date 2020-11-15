#include <iomanip>
#include "include/model/InfoBar.h"
#include "math.h"

template<typename T>
std::string to_string_with_precision(const T a_value, const int n = 1) {
    std::ostringstream out;
    out << std::setprecision(n) << a_value;
    return out.str();
}

void InfoBar::draw(RenderWindow &window) {
    Vector2f center = window.getView().getCenter();
    Vector2f size = window.getView().getSize();

    float barOriginX = center.x - size.x / 2 + 10;
    float barOriginY = center.y + size.y / 2 - 40;

    charsBar.setPosition(barOriginX, barOriginY);
    charsBar.setSize({size.x - 20, 30});
    charsBar.setOutlineColor(outLineColor);
    charsBar.setFillColor(fillColor);
    charsBar.setOutlineThickness(2);

    window.draw(charsBar);
    barOriginX += 5;

    for (const auto &ch: player->attributes) {
        Text text;
        text.setFont(font);
        text.setPosition(barOriginX, barOriginY + 2);
        text.setString(ch.first + ": " + to_string_with_precision(ch.second, 3));
        text.setCharacterSize(16);
        text.setFillColor(Color::Black);
        window.draw(text);
        barOriginX += text.getLocalBounds().left + text.getLocalBounds().width + 20;
    }

    float itemsBar1OriginX = center.x - size.x / 2 + 10;
    float itemsBar1OriginY = center.y - 40;

    itemsBar1.setPosition(itemsBar1OriginX, itemsBar1OriginY);
    itemsBar1.setSize({30, 180});
    itemsBar1.setOutlineColor(outLineColor);
    itemsBar1.setFillColor(fillColor);

    itemsBar1.setOutlineThickness(2);
    window.draw(itemsBar1);

    if (player->weapon != nullptr) {
        player->weapon->sprite.setScale(0.6, 0.6);
        player->weapon->sprite.setPosition(itemsBar1OriginX - 1, itemsBar1OriginY);
        window.draw(player->weapon->sprite);

        Text text;
        text.setFont(font);
        text.setPosition(itemsBar1OriginX + 13, itemsBar1OriginY + 25);

        text.setString(to_string_with_precision(player->weapon->getDamage(), 2));
        text.setFillColor(Color::Black);
        text.setCharacterSize(13);
        window.draw(text);
    }

    float potionsOriginY = itemsBar1OriginY;

    int index = 0;
    for (auto &potion : player->potions) {
        potionsOriginY += 30;
        potion->sprite.setScale(0.7, 0.7);
        potion->x = itemsBar1OriginX - 3;
        potion->y = potionsOriginY + 10;
        potion->sprite.setPosition(potion->x, potion->y);

        window.draw(potion->sprite);

        if (index == player->currentPotion) {
            RectangleShape usingPotion;
            usingPotion.setPosition(potion->x, potion->y + 10);
            usingPotion.setSize({size.x - size.x + 11, 2});
            usingPotion.setFillColor(outLineColor);
            window.draw(usingPotion);
        }
        index++;
    }

    float itemsBar2OriginX = center.x + size.x / 2 - 40;
    float itemsBar2OriginY = center.y - 40;

    itemsBar2.setPosition(itemsBar2OriginX, itemsBar2OriginY);
    itemsBar2.setSize({30, 180});
    itemsBar2.setOutlineColor(outLineColor);
    itemsBar2.setFillColor(fillColor);
    itemsBar2.setOutlineThickness(2);
    window.draw(itemsBar2);

    Text text;
    text.setFont(font);
    text.setPosition(itemsBar2OriginX + 7, itemsBar2OriginY + 5);

    text.setString(to_string_with_precision(player->calculateProtection(), 2));
    text.setFillColor(Color::Black);
    text.setCharacterSize(13);
    window.draw(text);

    float equipOriginY = itemsBar2OriginY + 10;

    for (auto &equipIndex : player->equipment) {
        if (equipIndex != nullptr) {
            equipIndex->sprite.setScale(0.7, 0.7);
            equipIndex->x = itemsBar2OriginX - 3;
            equipIndex->y = equipOriginY + 10;
            equipIndex->sprite.setPosition(equipIndex->x, equipIndex->y);
            window.draw(equipIndex->sprite);
        }
        equipOriginY += 30;
    }

    float keyOriginX = center.x + size.x / 2 - 40;
    float keyOriginY = center.y + size.y / 2 - 90;

    Sprite keySprite;
    Image keyImage;
    keyImage.loadFromFile("../res/img/items/key.png");
    Texture texture;
    texture.loadFromImage(keyImage);
    keySprite.setTexture(texture);

    keySprite.setPosition(keyOriginX, keyOriginY);
    keySprite.setScale(0.5, 0.5);
    text.setPosition(keyOriginX+15, keyOriginY+10);

    text.setString(to_string(player->bunchOfKeys.getSize()));
    text.setFillColor(Color::Black);
    text.setCharacterSize(13);
    window.draw(keySprite);
    window.draw(text);

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
