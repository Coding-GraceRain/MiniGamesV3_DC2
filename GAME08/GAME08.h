#pragma once
#include<vector>
#include "../MAIN/GAME_BASE.h"
namespace GAME08
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
		class ACTOR* court() { return Court; }
		class ACTOR* player() { return Player; }
		class ACTOR* ball() { return Ball; }
        class ACTOR* player2() { return Player2; }
        class ACTOR* score() { return Score; }
        class ACTOR* game() { return Game; }
        class ACTOR* title() { return Title; }
        void GameOver() { Playing = false; }
    private:
        void Init();
		std::vector<class ACTOR*> Actors;
        class ACTOR* Court;
		class ACTOR* Player;
		class ACTOR* Ball;
        class ACTOR* Player2;
        class ACTOR* Score;
        class ACTOR* Game;
        class ACTOR* Title;
        bool Playing = true;
        bool TitleFlag = true;
    };
}
