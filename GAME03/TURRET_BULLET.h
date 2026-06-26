#pragma once
#include "CHARACTER.h"
namespace GAME03
{
    class TURRET_BULLET :
        public CHARACTER
    {
    public:
        TURRET_BULLET(class GAME* game) :CHARACTER(game){}
        void create();
        void appear(float x, float y, float vx, float vy);
        void update();
    };
}
