#pragma once
#include "ENEMY.h"
namespace GAME01 {
    class BOSS :
        public ENEMY
    {
        void init(int IPx, int IPy);
        void draw();
    };
}
