#pragma once
#include "../MAIN/GAME_BASE.h"
namespace GAME06
{
    const int TOTAL_BULLETS = 10;
    const int FPS = 60;
    class GAME :
        public GAME_BASE
    {
    public:
        GAME(class MAIN* main) :GAME_BASE(main) {};
        ~GAME() {};
        int create();
        void proc();
        void destroy();
        void init();
        bool collision(class PLAYER* p, class BULLET* eb);
        bool collision(class ENEMY* e, class BULLET* pb);
        class PLAYER* player() { return Player; }
        class ENEMY* enemy() { return Enemy; }
    private:
        int Counter = 0;
        int PLAYER_BULLETS = 5;
        class PLAYER* Player = nullptr;
        class ENEMY* Enemy = nullptr;
        class BULLET* Bullet[TOTAL_BULLETS]{};
    };
}
