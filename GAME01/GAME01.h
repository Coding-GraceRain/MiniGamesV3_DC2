#pragma once
#include"../MAIN/GAME_BASE.h"
#include"MATH.h"
namespace GAME01
{
    class GAME :
        public GAME_BASE
    {
    private:
        int currentScene = 0;
    public:
        int c2 = 1;
        GAME(class MAIN* main) :GAME_BASE(main) {};
        ~GAME() {};
        int create();
        int file();
        void proc();
        void counter();
        void destroy();
        void draw();
        MATH* math();
    };
}

