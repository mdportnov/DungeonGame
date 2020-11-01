#include "main.h"

using namespace sf;

sf::View view;

void getPlayerCoordinateForView(float x, float y) {
    float tempX = x;
    float tempY = y;
    if (x < 320) tempX = 320;
    if (y < 240) tempY = 240;
    if (y > 554) tempY = 554;

    view.setCenter(tempX, tempY);
}

void viewMap(float time) {
    if (Keyboard::isKeyPressed(Keyboard::D)) {
        view.move(0.1 * time, 0);//скроллим карту вправо (см урок, когда мы двигали героя - всё тоже самое)
    }

    if (Keyboard::isKeyPressed(Keyboard::S)) {
        view.move(0, 0.1 * time);//скроллим карту вниз (см урок, когда мы двигали героя - всё тоже самое)
    }

    if (Keyboard::isKeyPressed(Keyboard::A)) {
        view.move(-0.1 * time, 0);//скроллим карту влево (см урок, когда мы двигали героя - всё тоже самое)
    }
    if (Keyboard::isKeyPressed(Keyboard::W)) {
        view.move(0, -0.1 * time);//скроллим карту вправо (см урок, когда мы двигали героя - всё тоже самое)
    }
}

void changeView() {
    if (Keyboard::isKeyPressed(Keyboard::LBracket)) {
        view.zoom(0.9994); //масштабируем, уменьшение
    }
    if (Keyboard::isKeyPressed(Keyboard::RBracket)) {
        view.zoom(1.0006f); //масштабируем, приближение
    }

    if (Keyboard::isKeyPressed(Keyboard::R)) {
        //view.setRotation(90);//сразу же задает поворот камере
        view.rotate(1);//постепенно поворачивает камеру (отрицательное значение - в обратную сторону)
    }


    if (Keyboard::isKeyPressed(Keyboard::I)) {
        view.setSize(640, 480);//устанавливает размер камеры (наш исходный)
    }

    if (Keyboard::isKeyPressed(Keyboard::P)) {
        view.setSize(540, 380);//например другой размер
    }


    if (Keyboard::isKeyPressed(Keyboard::Q)) {
        view.setViewport(sf::FloatRect(0, 0, 0.5f,1));
        //таким образом делается раздельный экран для игры на двоих. нужно только создать ещё один объект
        // View и привязывать к нему координаты игрока 2.
    }
}
