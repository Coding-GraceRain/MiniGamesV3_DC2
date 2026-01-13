#pragma once
namespace GAME04 {
    class ENEMY {
    public:
        float wx, wy = 800;
        float vx = -2;
        float pr = 25;
        int hp = 3;
        bool active = true;

        ENEMY(float x) :wx(x) {}
        void move();
        void draw();
    };
}