#pragma once
#include "CHARACTER.h"
namespace GAME03
{
    class BUTTON :
        public CHARACTER
    {
    public:
        struct DATA {
        };
    private:
        DATA Button;
    public:
        BUTTON(class GAME* game);
        ~BUTTON();
        void create();
        void appear(float x, float y, float vx, float vy);
        void update();
    };
}