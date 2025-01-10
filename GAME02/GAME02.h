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

        void setnum();
        void mousecol();
        void draw();
    private:

        enum STATE { TITLE, PLAY, CLEAR };
        STATE State = TITLE;

        struct SQUARE {
            float px;
            float py;
            float w;
            float h;

            int num;
            int ansnum;
        };


        struct FRAME {
            float px;
            float py;
            float w;
            float h;
        };

        int num_list[9];

        FRAME frame[3][3];
        SQUARE square[9][9];

    };
}
