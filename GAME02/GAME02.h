#pragma once
#include "../MAIN/GAME_BASE.h"
#include"PLAYER.h"
#include"ENEMY.h"
#include"haikei.h"
#include"BULLET.h"
#include"DEFINES.h"
#include"item.h"
#include "EBULLET.h"
#include "SHOT_POINT.h"
#include"Saveload.h"
#include "ENEMY2.h"
#include "BBULLET.h"

namespace GAME02
{
    class GAME :
        public GAME_BASE
    {  
  
    private:
        enum { TITLE, PLAY,OPTION, SIBARI, SIBARIOVER, GAMEOVER, CLEAR };
        int State;
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
    public:
        GAME(class MAIN* main) :GAME_BASE(main) {};
        ~GAME() {};  
    private:

        void Title();
        void Play();
        void GameOver();
        void SibariOver();
        void GameClear();
        void Sibarimode();
        void Init();
        bool AllDead();
        void Bossshot();
    public:
    
        int create();
        void proc();
        void destroy();
    };
}