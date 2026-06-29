#pragma once
#include "ACTOR.h"
namespace GAME08 {
    class BALL :
        public ACTOR
    {
    public:
        BALL(class GAME* game);
        ~BALL();
        void init();
        void update();
        void draw();
    private:
        void Move();
        void Wall();
        void Collision();
    };
}
