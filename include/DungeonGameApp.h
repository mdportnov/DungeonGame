#include "main.h"

namespace MyGame {
    class DungeonGameApp {
    protected:
        sf::RenderWindow *window;
    public:
        sf::SoundBuffer buffer1, buffer2, buffer3;
        sf::Sound doorSound, chestSound, mainSound;

        DungeonGameApp();

        ~DungeonGameApp();

        void Init();

        void Run();

        void End();

        void MusicInit();

        void playSound(std::string name);
    };
}
