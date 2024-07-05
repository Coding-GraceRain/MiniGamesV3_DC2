#pragma once
#include "BULLET.h"
namespace GAME06 
{
    class ENEMY_BULLET :
        public BULLET
    {
    public:
        ENEMY_BULLET();
        ~ENEMY_BULLET();
        void init();
        void draw();
        void shot();
    };
}
