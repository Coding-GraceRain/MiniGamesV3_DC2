#pragma once
#include "BULLET.h"
namespace GAME06 
{
    class PLAYER_BULLET :
        public BULLET
    {
    public:
        PLAYER_BULLET();
        ~PLAYER_BULLET();
        void init();
        void draw();
        void shot();
    };
}
