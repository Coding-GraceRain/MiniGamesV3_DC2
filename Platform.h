#pragma once
#include "../../libOne/inc/libOne.h"

namespace GAME00 {
    class Platform {
    public:
        float x, y, w, h;
        Platform(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {}
        void draw(float camX = 0, float camY = 0) {
            fill(100, 200, 100);
            rect(x - camX, y - camY, w, h);
        }
    };
}
