#pragma once

#include <include/model/ObjectOnField.h>

/**
 * Класс объекта двери. Дверь может мешать пройти игроку. НЕ может быть заперта
 */
class Door : public ObjectOnField {
public:
    bool isLocked;

    FloatRect getAreaRect();

    Door(Level &level, string &fileName, string &name, float x, float y, float w, float h, int layer, bool b);

    void update();

    /**
     * Изменение состояния двери
     */
    void changeDoorState();
};