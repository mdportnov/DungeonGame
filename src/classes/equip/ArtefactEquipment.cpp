#include "include/model/equip/ArtefactEquipment.h"

#include <utility>

ArtefactEquipment::ArtefactEquipment(Level &level, string &fileName, string &name, string &type, string &subType,
                                     float x, float y, float w, float h, int state, float protection, int eqType,
                                     int materialType, map<string, string> properties) : Equipment(
        level, fileName, name, type, subType, x, y, w, h, state, protection, eqType, materialType),
                                                                                         changesMapFromXML(std::move(
                                                                                                 properties)) {
    for (const auto &p: changesMapFromXML) {
        if (p.first != "protection" && p.first != "eqType"
            && p.first != "materialType" && p.first != "state") {
            changesListA.emplace_back(p.first, stof(p.second));
        }
    }

}
