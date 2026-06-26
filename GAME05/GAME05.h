#pragma once
#include "../MAIN/GAME_BASE.h"
#include "GAME.h"
namespace GAME05
{

    class GAME :
        public GAME_BASE
    {
    private:
        GAME_* GameCore = nullptr;
        
    public:
       
        GAME(class MAIN* main) :GAME_BASE(main) {};
        ~GAME() {};
        int create();
        void proc();

        void destroy();
    };
}
