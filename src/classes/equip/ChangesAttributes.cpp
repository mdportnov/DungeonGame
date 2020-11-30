#include "include/model/equip/ChangesAttributes.h"
#include "algorithm"

ChangesAttributes::ChangesAttributes(const map<string, string> &properties) {
    for (const auto &p: properties) {
        if (existingChars.end() != find(existingChars.begin(), existingChars.end(), p.first)) {
            changesListA.emplace_back(p.first, stof(p.second));
        }
    }
}
