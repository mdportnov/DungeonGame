#include "include/model/equip/ChangesAttributes.h"
#include "algorithm"

ChangesAttributes::ChangesAttributes(const map<string, string> &properties) {
    for (const auto &p: properties) {
        if (asdasd.end() != find(asdasd.begin(), asdasd.end(), p.first)) {
            changesListA.emplace_back(p.first, stof(p.second));
        }
    }
}
