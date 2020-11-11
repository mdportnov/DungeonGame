#include "include/model/equip/Weapon.h"

#include <utility>

Weapon::Weapon(string name) : name(std::move(name)) {}
