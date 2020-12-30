#include <include/model/Player.h>
#include "main.h"


/**
 * Главный класс игры, в функциях которого инициализируются игровые объекты,
 * создаёт основной цикл игры, обновляются параметры
 */
class DungeonGameApp {
public:
    sf::SoundBuffer buffer1, buffer2, buffer3;
    sf::Sound doorSound, chestSound, mainSound;

    DungeonGameApp();

    ~DungeonGameApp();

    /**
     *  Создание окна
     */
    void Init();

    /**
     *  Загрузка данных и их взаимодействие между собой
     */
    void Run();

    /**
     *  Закрытие окна
     */
    void End();

    /**
     *  Инициализация звуковых файлов игры
     */
    void MusicInit();
};
