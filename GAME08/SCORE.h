#pragma once
#include "ACTOR.h"
namespace GAME08
{
    class SCORE :
        public ACTOR
    {
    public:
        SCORE(class GAME* game);
        ~SCORE();
        void init();
        void update();
        void draw();
        void winner();
        int playerScore() { return PlayerScore; }
        int player2Score() { return Player2Score; }
    private:
        int PlayerScore;
        int Player2Score;
        bool ScoreFlag;
        int Winner;
    };
}