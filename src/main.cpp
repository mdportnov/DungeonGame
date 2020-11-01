#include "include/TApplication.h"

int main() {
    MyGame::TApplication App;
    App.Init();
    App.Run();
    App.End();

    return 0;
}
