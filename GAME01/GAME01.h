#pragma once
#include "../MAIN/GAME_BASE.h"
namespace GAME01
{
    class GAME1;

    class GAME :
        public GAME_BASE
    {
    public:
        GAME1* game;
        GAME(class MAIN* main) :GAME_BASE(main) {};
        ~GAME() {};
        int create();
        void proc();
        void destroy();
        void backToMenu();
    };
}
