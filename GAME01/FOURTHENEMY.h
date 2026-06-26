#pragma once
#include "ENEMY.h"
namespace GAME01 {
    class FOURTHENEMY :
        public ENEMY
    {
    public:
        void init(int IPx, int IPy)override;
        void draw()override;
    };
}

