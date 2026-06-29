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

    private:
        int PlayerScore;
        int Player2Score;
        bool ScoreFlag;
        int WinerScore;
    };
}