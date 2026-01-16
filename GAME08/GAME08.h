#pragma once
#include "../MAIN/GAME_BASE.h"
#include "Board.h"

namespace GAME08
{
    class GAME :public GAME_BASE{
    public:
        GAME(class MAIN* main);
        ~GAME() {}

        int create();
        void proc();
        void destroy();

    private:

        Board* board; // É`ÉFÉXî’
        
    };
}