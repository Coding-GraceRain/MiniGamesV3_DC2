#pragma once
namespace GAME04 {
    class PLAYER {
    public:
        float wx = 200, wy = 800;
        float vx = 0, vy = 0;
        float pr = 30;
        int hp = 10;
        bool onGround = true;

        void move();
        void draw();
    };
}