#pragma once
#include "../MAIN/GAME_BASE.h"
#include"2D_MARIO.h"
namespace GAME12
{
    class GAME :
        public GAME_BASE
    {
    public:
        GAME(class MAIN* main) :GAME_BASE(main) {};
        ~GAME() {};
        int create();
        void proc();
        void destroy();
        class MARIO* mario = { 0 };
    };
}
