#pragma once
#include "ACTOR.h"
namespace GAME08
{
    class PLAYER2 :
        public ACTOR
    {
    public:
        PLAYER2(class GAME* game);
        ~PLAYER2();
        void init();
        void update();
        void draw();
    };
}

