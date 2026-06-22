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
#include "BBULLET2.h"
#include "ENEMY3.h"
#include "ZIKINERAI.h"
namespace GAME02
{
    class GAME :
        public GAME_BASE
    {  
    protected:
        int State;
        int BossState;
        enum { TITLE, PLAY, OPTION, HARD, HARDOVER, GAMEOVER, CLEAR };
        enum { NOPOP, BOSSPOP };
        float ShotDelay;
        float Delay;
        float Hdelay;
        int ShotCount;
        int ShotPoint;
        int Wave;
        int Score;
        int HighScore;
        float Deg[2]{};
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
        ENEMY3 Enemy3[ENEMY3_NUM];
        BOSS Boss;
        BACK Background;
        BULLET Bullet[BULLET_NUM];
        EBULLET Ebullet[BULLET_ENUM];
        ZIKINERAI Zikinerai[ZIKINERAI_NUM];
        SHOTPOINT Shotpoint[SHOT_POINT];
        SAVELOAD Save;
        BBULLET Bbullet[BULLET_BNUM];
        BBULLET2 Bbullet2[BULLET_BNUM];
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
        
        void TitleMainText();
        void PlayTexts();
        void GameOverTexts();
        void GameClearTexts();

        void Init();

        bool AllDead();
        void AllInit();
        void AllDraw();
        void AllUpdate();
        void AllCreate();

        void Hits();
        void Waves();
        void OptionProcess();
        void AmmoProcess();
        void BossProcess();

        void Bossshot();
    public:
      
        int create();
        void proc();
        void destroy();
    };
}