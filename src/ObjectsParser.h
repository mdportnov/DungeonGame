#include <include/TinyXML/tinyxml.h>
#include <include/model/Player.h>
#include <list>
#include <include/model/Enemy.h>

class ObjectsParser {
public:
    static void saveToFileProgress(const Level &level, const Player &player, const std::list<Enemy *> &enemiesList) {
        TiXmlDocument doc;
        auto *decl = new TiXmlDeclaration("1.0", "utf-8", "");
        doc.LinkEndChild(decl);
        TiXmlElement *root;
        root = new TiXmlElement("objects");
        root->SetAttribute("version", "1.0");
        doc.LinkEndChild(root);

        TiXmlElement *unit;
        auto *units = new TiXmlElement("units");
        root->LinkEndChild(units);

//        for (auto layers: level.getCountOfLayers())

            for (auto enemy: enemiesList) {
                unit = new TiXmlElement("object");
                unit->SetAttribute("name", enemy->name.c_str());
                unit->SetDoubleAttribute("x", enemy->x);
                unit->SetDoubleAttribute("y", enemy->y);
                unit->SetDoubleAttribute("width", enemy->w);
                unit->SetDoubleAttribute("height", enemy->h);
                units->LinkEndChild(unit);
            }

        unit = new TiXmlElement("object");
        unit->SetAttribute("name", player.name.c_str());
        unit->SetDoubleAttribute("x", player.x);
        unit->SetDoubleAttribute("y", player.y);
        unit->SetDoubleAttribute("width", player.w);
        unit->SetDoubleAttribute("height", player.h);

        units->LinkEndChild(unit);


        auto characteristics = new TiXmlElement("characteristics");
        root->LinkEndChild(characteristics);

        auto equipment = new TiXmlElement("equipment");
        root->LinkEndChild(equipment);



        doc.SaveFile("/home/mikhail/Desktop/sfml_test/res/level1objectss.xml");
    }

    static void loadFromFileProgress(const Level &level, const Player &player, const std::list<Enemy *> &enemiesList) {

    }
};
