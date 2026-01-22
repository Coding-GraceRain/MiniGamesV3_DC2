#pragma once
#include <vector>

namespace GAME00 {

    class Platform;

    class Player {
    public:
        float x = 0;
        float y = 0;
        float vx = 0;
        float vy = 0;

        float width = 40;
        float height = 60;

        bool onGround = false;
        bool onWall = false;

        float coyoteTimer = 0.0f;
        const float coyoteTime = 0.1f;

        void init(float startX, float startY) {
            x = startX;
            y = startY;
            vx = vy = 0;
            onGround = onWall = false;
            coyoteTimer = 0;
        }

        void update(const std::vector<Platform>& platforms);
        void draw(float camX, float camY);
    };

}
