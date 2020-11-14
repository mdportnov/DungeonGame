#include "include/model/equip/Key.h"

Key::Key(Level &level, string &fileName, string &name, string &type, string &subType, float x, float y, float w,
         float h, int state) : Item(level, fileName, name, type, subType, x, y, w, h, state) {}
