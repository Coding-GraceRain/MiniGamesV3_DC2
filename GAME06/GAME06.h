#pragma once
#include "../MAIN/GAME_BASE.h"
#include"player.h"
#include"item.h"
#include "back.h"
namespace GAME06
{
    class GAME :
        public GAME_BASE
    {
    private:
        enum { TITLE,EXP, PLAY, RESULT };
        int State=0;
        int Sound = 0;
        int Sound2 = 0;
        PLAYER player;
        ITEM item;
        BACK back;
    public:
        GAME(class MAIN* main) :GAME_BASE(main) {};
        ~GAME() {};
        void init();
        int create();
        void exp();
        void update();
        void result();
        void proc();
        void destroy();
    };
}
