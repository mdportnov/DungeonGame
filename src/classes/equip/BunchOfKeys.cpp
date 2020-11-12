#include "include/model/equip/BunchOfKeys.h"

void BunchOfKeys::addNewOne() {
    if (size == maxSize)
        return;
    size++;
}

void BunchOfKeys::brokeKey() {
    if (size > 0)
        size--;
}
