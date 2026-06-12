#pragma once
#include "../MAIN/GAME_BASE.h"
#include"PLAYER.h"
#include"ENEMY.h"
#include"haikei.h"
#include"BULLET.h"
#include"DEFINES.h"
#include"ITEM.h"
#include "EBULLET.h"
#include "SHOT_POINT.h"
#include"Saveload.h"
#include "ENEMY2.h"
#include "BBULLET.h"
#include "SOUNDS.h"
namespace GAME02
{
    class GAME :
        public GAME_BASE
    {  
    protected:
        int State;
        enum { TITLE, PLAY, OPTION, HARD, HARDOVER, GAMEOVER, CLEAR };
        float ShotDelay;
        float Delay;
        float Hdelay;
        int ShotCount;
        int ShotPoint;
        int Wave;
        int Score;
        int HighScore;
        float Deg;
        int offsetx[SHOT_POINT] =
        {
            30,-30,55,-55
        };
        int offsety[SHOT_POINT] =
        {
            50, 50, 0, 0
        };
        int Cur = 0;
        int Choose[3];
        POINT mouse;
        PLAYER Player;
        ITEM Item[ITEM_NUM];
        ENEMY Enemy[ENEMY_NUM];
        BOSS Boss;
        BACK Background;
        BULLET Bullet[BULLET_NUM];
        EBULLET Ebullet[BULLET_ENUM];
        SHOTPOINT Shotpoint[SHOT_POINT];
        SAVELOAD Save;
        BBULLET Bbullet[BULLET_BNUM];
        SOUNDS Sound;
    public:
        GAME(class MAIN* main) :GAME_BASE(main) {};
        ~GAME() {};  
    private:

        void Title();
        void Play();
        void GameOver();
        void HardOver();
        void GameClear();
        void Hardmode();
        void Option();
        void Init();
        bool AllDead();
        void Bossshot();
    public:
      
        int create();
        void proc();
        void destroy();
    };
}