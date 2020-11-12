cmake_minimum_required(VERSION 3.17)
project(DungeonGame)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(/src/)

set(TINY_SOURCES "include/TinyXML/tinyxml.h"
        "include/TinyXML/tinystr.h"
        "include/TinyXML/tinystr.cpp"
        "include/TinyXML/tinyxml.cpp"
        "include/TinyXML/tinyxmlparser.cpp"
        "include/TinyXML/tinyxmlerror.cpp")

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(DungeonGame
        src/main.cpp
        include/main.h
        src/DungeonGameApp.cpp
        include/DungeonGameApp.h
        include/model/Player.h
        include/model/equip/Artefact.h
        include/model/equip/ArtefactEquipment.h
        include/model/equip/ArtefactWeapon.h
        include/model/equip/BunchOfKeys.h
        include/model/table/Characteristic.h
        include/model/Chest.h
        include/model/equip/EnchantedArtefactWeapon.h
        include/model/equip/EnchantedWeapon.h
        include/model/equip/Equipment.h
        include/model/equip/EquipmentMaterials.h
        include/model/Item.h
        include/model/ObjectOnField.h
        include/model/equip/Potion.h
        include/model/table/TableOfCharacteristics.h
        include/model/Unit.h
        include/model/equip/Weapon.h
        include/model/Enemy.h
        include/model/Level.h
        include/model/ObjectsParser.h
        src/classes/Level.cpp include/model/Level.h

        ${TINY_SOURCES}
        src/classes/ObjectOnField.cpp include/model/MyView.h src/classes/Unit.cpp src/classes/Player.cpp src/classes/MyView.cpp src/classes/Enemy.cpp src/classes/Item.cpp include/model/MapObject.h src/classes/MapObject.cpp include/model/Layer.h src/classes/Layer.cpp src/classes/Door.cpp include/model/Door.h src/classes/Chest.cpp src/classes/equip/Weapon.cpp src/classes/equip/Potion.cpp src/classes/equip/BunchOfKeys.cpp src/classes/equip/Key.cpp include/model/equip/Key.h)

target_link_libraries(DungeonGame sfml-graphics sfml-audio)