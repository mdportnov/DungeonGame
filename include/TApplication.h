#include "main.h"
namespace MyGame {
    class TApplication {
    protected:
        sf::RenderWindow *window;
    public:
        TApplication();
        ~TApplication();
        void Init();
        void Run();
        void End();
    };
}
