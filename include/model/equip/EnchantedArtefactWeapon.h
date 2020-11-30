#pragma once

#include "EnchantedWeapon.h"
#include "ArtefactWeapon.h"

/**
 * Класс зачарованного артефактного оружия
 */

class EnchantedArtefactWeapon : public EnchantedWeapon, public ArtefactWeapon {
public:
    EnchantedArtefactWeapon(Level &level, string &fileName, string &name, string &type,
                            string &subType, float x, float y, float w, float h, int layer, int state,
                            float damage, const map<string, string>& properties);

    void draw(RenderWindow &window);
};