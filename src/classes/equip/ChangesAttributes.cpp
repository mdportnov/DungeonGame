#include "include/model/equip/ChangesAttributes.h"

ChangesAttributes::ChangesAttributes(const map<string, string> &properties) {
    for (const auto &p: properties) {
        if (p.first.length() == 2) {
            changesListA.emplace_back(p.first, stof(p.second));
        }
    }
}
