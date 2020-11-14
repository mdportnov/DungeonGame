#include <include/TinyXML/tinyxml.h>
#include <random>
#include <iostream>
#include "include/DungeonGameApp.h"


int main() {
    MyGame::DungeonGameApp App;
    App.Init();
    App.Run();
    App.End();

    return 0;
}
