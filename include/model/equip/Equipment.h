#include "src/model/Item.h"
#include "Artefact.h"
#include "EnchantedWeapon.h"

enum class EquipmentTypes {
    HELMET, BREASTPLATE, BOOTS
};

class Equipment : public Item, public Artefact, public EnchantedWeapon {
public:
    string type;
    int protection;
    string material;
};