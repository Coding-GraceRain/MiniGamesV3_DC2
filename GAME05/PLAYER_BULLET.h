#pragma once
#include "CHARACTER.h"
namespace GAME05 {
    class PLAYER_BULLET :
        public CHARACTER
    {
    public:
        PLAYER_BULLET(class GAME_* game) :CHARACTER(game) {}
        void create();
        void appear(float wx, float wy, float vx, float vy);
        void update();
    };
}
