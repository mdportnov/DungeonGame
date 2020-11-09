#include "../main.h"

class ObjectOnField {
public:

    float x, y, w, h;
    Texture texture;
    Sprite sprite;
    Level level;

    ObjectOnField(float x, float y, float w, float h, Level &level) {
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
        this->level = level;
    };
};