cmake_minimum_required(VERSION 3.17)
project(DungeonGame)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(DungeonGame
        src/main.cpp
        include/main.h src/TApplication.cpp include/TApplication.h)

target_link_libraries(DungeonGame sfml-graphics sfml-audio)
