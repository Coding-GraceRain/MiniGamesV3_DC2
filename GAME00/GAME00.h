#pragma once
#include "../MAIN/GAME_BASE.h"
#include"PLAYER.h"
#include"ENEMY.h"
#include"OBJECT.h"
#include"OBJECT2.h"
#include"FLAG.h"
namespace GAME00
{
    class GAME :
        public GAME_BASE
    {
    private:
        enum { TITLE, PLAY, GAMEOVER,CLEAR };
        int State;
        int BackGroundImg;
        int HpImg;
        int EmptyHpImg;
        int Bgm;
        int PushSe;
        int GetSe;
        int GameOverSe;
        PLAYER Player;
        static const int Enum = 3;
        ENEMY Enemies[Enum];
        OBJECT Object;
        static const int Obj2_Max = 30;
        OBJECT2 Object2[Obj2_Max];
        FLAG Flag;
        float Pbx, Pby, Pbw, Pbh;
        bool isMouseOnPlay(int x,int y,int w,int h);
        float StartWorldY;
        float WorldScrollY;
        float TimeLimit;
    public:
        GAME(class MAIN* main) :GAME_BASE(main) {};
        ~GAME() {};
        int create();
    private:
        void Title();
        void Play();
        void Clear();
        void GameOver();
        void ResetGame();
        void RePlay();
        void Object2Init();
        void EnemiesInit();
        void TimeInit();
    public:
        void proc();
        void destroy();
    };
}
