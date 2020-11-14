#ifndef DUNGEONGAME_INFOBAR_H
#define DUNGEONGAME_INFOBAR_H

#include "../main.h"
#include "Player.h"

using namespace sf;

class InfoBar {
private:
    Player *player;
public:
    RectangleShape charsBar;
    RectangleShape itemsBar1;
    RectangleShape itemsBar2;

    Color outLineColor = Color(132, 36, 110);
    Color fillColor = Color(255, 231, 186);

    Font font;

    InfoBar();

    void draw(RenderWindow &window);

    void observe(Player *p);
};


#endif //DUNGEONGAME_INFOBAR_H
