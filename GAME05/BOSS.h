#pragma once
#include "CHARACTER.h"
namespace GAME05 {
    class BOSS :
        public CHARACTER
    {
    public:
        struct DATA {
            float elapsedTime = 0;
            float interval = 0;
            int triggerCnt = 0;
            int triggerInterval = 0;
            int trigger1st = 0;
            int trigger2nd = 0;
            int trigger3rd = 0;
            int trigger4th = 0;
            int trigger5nd = 0;
            int trigger6rd = 0;
            int trigger7th = 0;
            int moveState = 0;   // 0:âE 1:â∫ 2:ç∂ 3:è„
            float moveStartX = 0;
            float moveStartY = 0;
            float bulletOffsetX = 0;
            char bulletCharaId = 0;
            float damageTime = 0;
            float damageInterval = 0;
            char explosionCharaId = 0;
            COLOR damageColor;
            COLOR normalColor;
        };
    private:
        DATA Boss;
    public:
        BOSS(class GAME_* game) :CHARACTER(game) {}
        void create();
        void appear(float wx, float wy, float vx, float vy);
        void Move();
        void update();
        void damage();
    };
}