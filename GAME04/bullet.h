#pragma once
namespace GAME04 {
    class BULLET {
    public:
        float wx, wy;
        float vx = 12;
        float pr = 10;
        int hp = 0;

        void shoot(float x, float y);
        void move();
        void draw();
    };
}