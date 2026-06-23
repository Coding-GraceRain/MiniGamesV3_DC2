#pragma once
#include "../MAIN/GAME_BASE.h"
#include "../MAIN/MAIN.h"
#include"PROMANE.h"
namespace GAME02
{
    class GAME :
        public GAME_BASE
    {  
    protected:
        PROMANE Promane;
    public:
        GAME(class MAIN* main) :GAME_BASE(main) {};
        ~GAME() {};  
    private:

        void Title();
        void Play();
        void GameOver();
        
        void GameClear();
        void Option();
      
    public:
      
        int create();
        void proc();
        void destroy();
    };
}