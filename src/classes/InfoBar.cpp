#include "include/model/InfoBar.h"

void InfoBar::draw(RenderWindow &window) {
    Vector2f center = window.getView().getCenter();
    Vector2f size = window.getView().getSize();

    s.setPosition(center.x - size.x / 2 + 10, center.y - size.y / 2 + 10);//позиция на экране
    bar.setPosition(center.x - size.x / 2 + 14, center.y - size.y / 2 + 14);

    window.draw(s);//сначала рисуем полоску здоровья
    window.draw(bar);//поверх неё уже черный прямоугольник, он как бы покрывает её
}

void InfoBar::update(float k)// k-текущее здоровье
{
    if (k > 0)
        if (k < max)
            bar.setSize(Vector2f(10, (max - k) * 70 /
                                     max));//если не отрицательно и при этом меньше максимума, то устанавливаем новое значение (новый размер) для черного прямоугольника
}

InfoBar::InfoBar() {
    image.loadFromFile("../res/img/life.png");
    image.createMaskFromColor(Color(50, 96, 166));
    t.loadFromImage(image);
    s.setTexture(t);
    s.setTextureRect(IntRect(783, 2, 15, 84));
    bar.setFillColor(
            Color(0, 0, 0));//черный прямоугольник накладывается сверху и появляется эффект отсутствия здоровья
    max = 100;
}