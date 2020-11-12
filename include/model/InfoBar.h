#ifndef DUNGEONGAME_INFOBAR_H
#define DUNGEONGAME_INFOBAR_H

#include "../main.h"

using namespace sf;

class InfoBar {
public:
    Image image;
    Texture t;
    Sprite s;
    int max=200;
    RectangleShape bar;

    InfoBar();

    void update(float k);

    void draw(RenderWindow &window);

};


#endif //DUNGEONGAME_INFOBAR_H
