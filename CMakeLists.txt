cmake_minimum_required(VERSION 3.17)
project(DungeonGame)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(/src/)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(DungeonGame
        src/main.cpp
        include/main.h src/TApplication.cpp include/TApplication.h src/Player.cpp include/Player.h

        src/model/Artefact.h
        src/model/ArtefactEquipment.h
        src/model/ArtefactWeapon.h
        src/model/BunchOfKeys.h
        src/model/Cell.h
        src/model/CellType.h
        src/model/CellWithChest.h
        src/model/CellWithItem.h
        src/model/Characteristic.h
        src/model/Characteristics.h
        src/model/Chest.h
        src/model/EnchantedArtefactWeapon.h
        src/model/EnchantedWeapon.h
        src/model/Enemy.h
        src/model/Equipment.h
        src/model/EquipmentMaterials.h
        src/model/EquipmentTypes.h
        src/model/Game.h
        src/model/Hero.h
        src/model/Inventory.h
        src/model/Item.h
        src/model/Iterator.h
        src/model/Key.h
        src/model/LastPositions.h
        src/model/Level.h
        src/model/Map.h
        src/model/ObjectOnField.h
        src/model/PointType.h
        src/model/Potion.h
        src/model/Shortnames.h
        src/model/TableOfCharacteristics.h
        src/model/Unit.h
        src/model/Weapon.h
        )

target_link_libraries(DungeonGame sfml-graphics sfml-audio)
