#include "include/DungeonGameApp.h"

int main() {
    MyGame::DungeonGameApp App;
    App.Init();
    App.Run();
    App.End();

    return 0;
}
