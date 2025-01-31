#pragma once
#include "../MAIN/GAME_BASE.h"
namespace GAME02
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

        void title();
        void play();
        void gameclear();

        bool numCheck(int x, int y, int num);
        bool ansNumCheck(int x, int y, int num);
        bool setnum();
        bool solveQ(int& solutionCount);
        void createQ();

        bool clearCheck();

        void numcopy();
        void playMousecol();
        void playDraw();
        bool titleMousecol();
        void titleDraw();
    private:

        enum STATE { TITLE, PLAY, CLEAR };
        STATE State = TITLE;

        struct SQUARE {
            float px;
            float py;
            float w;
            float h;

            int num;
            int candidateNum[3][3];

            int ansnum;

            bool emptyFlag;
            bool ansNumFlag;
            bool clickFlag;
            bool identicalNumFlag;
        };

        struct BUTTON {
            float px;
            float py;
            float w;
            float h;

            int num;

            bool selectFlag;
            bool nineNumFlag;
        };

        struct FRAME {
            float px;
            float py;
            float w;
            float h;
        };

        SQUARE square[9][9];

        BUTTON titleButton[3];

        BUTTON resetButton;
        BUTTON titleReturnButton;

        BUTTON numButton[3][3];
        BUTTON candidateNumButton[3][3];
        FRAME frame[3][3];
        
        int SolutionCount;
        int deleteNum;
        int levelDifficulty;
        int colTime;
        int snd[3];
        
        bool clearFlag;
        bool once;
    };
}
