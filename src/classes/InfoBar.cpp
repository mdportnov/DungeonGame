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
        player->weapon->sprite.setScale(0.6, 0.6);
        player->weapon->sprite.setPosition(itemsBarOriginX - 1, itemsBarOriginY);
        window.draw(player->weapon->sprite);

        Text text;
        text.setFont(font);
        text.setPosition(itemsBarOriginX + 13, itemsBarOriginY + 25);

        text.setString(to_string_with_precision(player->weapon->getDamage(), 2));
        text.setFillColor(Color::Black);
        text.setCharacterSize(13);
        window.draw(text);
    }

    float potionsOriginY = itemsBarOriginY;

    int index = 0;
    for (auto &potion : player->potions) {
        potionsOriginY += 30;
        potion.sprite.setScale(0.7, 0.7);
        potion.x = itemsBarOriginX - 3;
        potion.y = potionsOriginY + 10;
        potion.sprite.setPosition(potion.x, potion.y);

        window.draw(potion.sprite);

        if (index == player->currentPotion) {
            RectangleShape usingPotion;
            usingPotion.setPosition(potion.x, potion.y + 10);
            usingPotion.setSize({size.x - size.x + 11, 2});
            usingPotion.setFillColor(Color::Red);
            window.draw(usingPotion);
        }
        index++;
    }

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
