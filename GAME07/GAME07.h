#pragma once
#include "../MAIN/GAME_BASE.h"
namespace GAME07
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
    private:
        enum GameState {
            TITLE,
            YAKU,
            INIT,
            OYA,
            PLAY,
            WIN,
            LOSE,
            DRAW
        };
        GameState State = TITLE;
        void Title();
        void Yaku();
        void Init();
        void Oya();
        void Play();
        void Win();
        void Lose();
        void Draw();
        int backImg;
        int dice1Img;
        int dice2Img;
        int dice3Img;
        int dice4Img;
        int dice5Img;
        int dice6Img;
        int oyaImg;
        int yakuImg;

        int playerSnd;
        int oyaSnd;

        int oyaDice[3];
        int playerDice[3];

        float px;
        float py = 600;

        bool oyaRolled = false;
        bool playerRolled = false;

        int oyaYaku;
        int playerYaku;

        int oyaPair;
        int playerPair;
        int oyaZorome;
        int playerZorome;

        
        bool ohas1;
        bool ohas2;
        bool ohas3;
        bool ohas4;
        bool ohas5;
        bool ohas6;
        bool phas1;
        bool phas2;
        bool phas3;
        bool phas4;
        bool phas5;
        bool phas6;
    };
}
