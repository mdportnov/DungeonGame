#include "include/model/MapObject.h"

int MapObject::getPropertyInt(std::string name) {
    return atoi(properties[name].c_str());
}

float MapObject::getPropertyFloat(std::string name) {
    return strtod(properties[name].c_str(), nullptr);
}

std::string MapObject::getPropertyString(std::string name) {
    return properties[name];
}