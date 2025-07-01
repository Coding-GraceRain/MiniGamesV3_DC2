#pragma once
#include "../MAIN/GAME_BASE.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "ebullet.h"

namespace GAME04
{
    class GAME :
        public GAME_BASE{

    public:
        GAME(class MAIN* main) :GAME_BASE(main) {};
        ~GAME() { destroy(); };
        int create();
        void proc();
        void destroy();
        void move();
        void draw();
        class PLAYER* player = nullptr;
        class ENEMY* enemy = nullptr;
        class BULLET* bullet = nullptr;
        class ENEMYBULLET* ebullet = nullptr;
        static const int MAX_BULLET = 1000;
        BULLET bullets[MAX_BULLET];
        ENEMYBULLET ebullets[MAX_BULLET];

        int enemyShootTimer = 0;
        
    };
}
