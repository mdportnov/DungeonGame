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
    RectangleShape itemsBar;

    Font font;

    InfoBar();

    void update();

    void draw(RenderWindow &window);

    void observe(Player *p);
};


#endif //DUNGEONGAME_INFOBAR_H
