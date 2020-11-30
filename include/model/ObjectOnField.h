#pragma once

#include "Level.h"

using namespace sf;

/**
  *  Класс любого объекта на карте, имеющего координаты, тип, имя файла текстуры и т.д.
  */
class ObjectOnField {
public:
    string fileName, type, subType, name;
    float x, y, w, h;
    int layer;
    Texture texture;
    Sprite sprite;
    Level level;
    Image image;
    Font font;
    /**
     * Получаем четырехугольник объекта
     */
    virtual FloatRect getRect() { return {x, y, w, h}; }

    ObjectOnField(Level &level, string &fileName, string &name, float x, float y, float w, float h, int layer);

    /**
     * Отрисовывает текстуру объекта в нужном месте
     * @param window отвечает за окно, в котором всё отрисовывается
     */
    virtual void draw(RenderWindow &window);

    /**
     * Обновляет состояние объекта с учётом обстоятельств,
     * зависящих от реализации класса-наследника
     * @param time отвечает за счётчик времени, передаваемый
     * из главного цикла игры
     */
    virtual void update(float time);
};