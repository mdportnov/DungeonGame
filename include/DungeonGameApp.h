#include "main.h"
namespace MyGame {
    class DungeonGameApp {
    protected:
        sf::RenderWindow *window;
    public:
        DungeonGameApp();
        ~DungeonGameApp();
        void Init();
        void Run();
        void End();
    };
}
