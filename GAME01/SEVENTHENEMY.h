#pragma once
#include "ENEMY.h"
namespace GAME01 {
    class SEVENTHENEMY :
        public ENEMY
    {
        void init(int IPx, int IPy);
        void draw();
    };
}