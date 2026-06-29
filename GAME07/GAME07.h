#pragma once
#include "../MAIN/GAME_BASE.h"
#include "TAITLE.h"
namespace GAME07
{
    class GAME :
        public GAME_BASE
    {
    private:
        TAITLE taitle;
    public:
        GAME(class MAIN* main) :GAME_BASE(main) {
        };
        ~GAME() {};
        int create();
        void proc();
        void destroy();
    };
}
