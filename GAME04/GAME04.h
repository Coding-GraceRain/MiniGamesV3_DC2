#pragma once
#include "../MAIN/GAME_BASE.h"
#include "PLAYER.h"
#include "ENEMY.h"
namespace GAME04
{
    class GAME :
        public GAME_BASE
        
    {
    private:
        enum { TITLE,INFO,CONTROL, PLAY, GAMEOVER ,CLEAR};
        int state;
        int score;
        int imgMenu[3];     //0:press space 1:contorl 2:exit
        int select=0; 
        int imgTitle;
        int imgOtaku = 0;
        int imgSoldier[3];
        int imgHaikei;
        int imgKoumori[3];
        int imgObake[3];
        int imgcarsol;
        int imgcontrolgamen;
        int imginfo;
        int imgcleargamen;
        int imgClearEffect[10];
        int imgGoal;
        float haikeix;
        float speed;
        float bx[10];
        float by[10];
        int fx[3];  //asiba kutyu
        int fy[3];
        float gx, gy;
        int ginit;
        bool bActive[10];
        int distance;
        int drawTimer = 0;
        int drawTime = 0;
        int drawTime2 = 0;
        int seJump;
        bool efectend;
        bool clearinit;
       // int bgm;
    public:
        GAME(class MAIN* main) :GAME_BASE(main) {};
        ~GAME() {};

        PLAYER player;
        OBAKE obake[5];
        KOUMORI koumori[5];

        int create();
        void proc();
        void init();
        void destroy();
        void collision();
    };

}
