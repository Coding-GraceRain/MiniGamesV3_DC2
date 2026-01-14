#pragma once
#include<cstdint>
#include "../MAIN/GAME_BASE.h"

#include"GAME_GRAPHIC.h"
#include"PLAYER_and_NPC.h"
#include"GAME_SCENE.h"
#include"TITLE_SELECT.h"

namespace GAME11
    //âΩåÃÇ©width,heightÇ™ìÆçÏÇµÇ»Ç≠Ç»Ç¡ÇΩÇÃÇ≈ë„óp.
#define Yoko 1920
#define Tate 1080
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
        class PLAYER* player = { 0 };
        class GAME_SCENE* game_scene = { 0 };
        class MAP* map = { 0 };
        class ENEMY* enemy[50] = { 0 };
        class SELECT* select = { 0 };
        class BOSS* boss = { 0 };
        //struct BULLET bullet[32];
        //class PLAYER_STATUS* player_status;
        //class ATTACK* attack;
    };
}
