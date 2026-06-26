#pragma once
#include "CHARACTER.h"
namespace GAME03
{
    class TURRETS :
        public CHARACTER
    {
    public:
        struct DATA {
            float elapsedTime = 0;
            float interval= 0;
            int triggerCnt = 0;
            int triggerInterval = 0;
            int trigger1st = 0;
            int trigger2nd = 0;
            int trigger3rd = 0;
            int trigger4th = 0;
            float bulletOffsetX = 0;
            float bulletOffsetY = 0;
            char bulletCharaId = 0;
        };
    private:
        DATA Turret;
    public:
        TURRETS(class GAME* game);
        ~TURRETS();
        void create();
        void appear(float x, float y, float vx, float vy);
        void update();
    };
}
