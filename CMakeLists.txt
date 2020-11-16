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
        include/model/equip/ArtefactEquipment.h
        include/model/equip/Weapon.h
        include/model/equip/ArtefactWeapon.h
        include/model/equip/EnchantedWeapon.h
        include/model/equip/EnchantedArtefactWeapon.h
        include/model/equip/BunchOfKeys.h
        include/model/Chest.h
        include/model/equip/Equipment.h
        include/model/Item.h
        include/model/ObjectOnField.h
        include/model/equip/Potion.h
        include/model/Unit.h
        include/model/Enemy.h
        include/model/Level.h
        include/model/ObjectsParser.h
        include/model/Layer.h
        include/model/equip/Key.h
        include/model/MyView.h
        include/model/InfoBar.h
        include/model/Door.h
        include/model/MapObject.h
        src/classes/Level.cpp include/model/Level.h
        src/classes/ObjectOnField.cpp
        src/classes/Unit.cpp
        src/classes/Player.cpp
        src/classes/MyView.cpp
        src/classes/Enemy.cpp
        src/classes/Item.cpp
        src/classes/MapObject.cpp
        src/classes/Layer.cpp
        src/classes/Door.cpp
        src/classes/Chest.cpp
        src/classes/equip/Weapon.cpp
        src/classes/equip/Potion.cpp
        src/classes/equip/BunchOfKeys.cpp
        src/classes/equip/Key.cpp
        src/classes/InfoBar.cpp
        src/classes/equip/Equipment.cpp
        src/classes/equip/EnchantedWeapon.cpp
        src/classes/equip/ArtefactEquipment.cpp
        src/classes/equip/ArtefactWeapon.cpp
        src/classes/equip/EnchantedArtefactWeapon.cpp
        ${TINY_SOURCES}
        )

target_link_libraries(DungeonGame sfml-graphics sfml-audio)