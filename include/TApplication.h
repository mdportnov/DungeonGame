#ifndef SFML_TEST_TAPPLICATION_H
#define SFML_TEST_TAPPLICATION_H

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
#endif
