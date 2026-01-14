#pragma once
#include "../MAIN/GAME_BASE.h"
#include"GAME_SCENE_CHANGE.h"
#include"Minesweeper.h"
#include"DASSYUTU.h"
namespace GAME13
{
    //âΩåÃÇ©width,heightÇ™ìÆçÏÇµÇ»Ç≠Ç»Ç¡ÇΩÇÃÇ≈ë„óp.
#define Yoko 1920
#define Tate 1080

    class GAME :
        public GAME_BASE
    {
    public:
        GAME(class MAIN* main) :GAME_BASE(main) {};
        ~GAME() {};
        int create();
        void proc();
        void destroy();
        class GAME_SCENE* game_scene = { 0 };
        class MINESWEEPER* minesweeper = { 0 };
        class DASSYUTU* dassyutu = { 0 };
    };
}
