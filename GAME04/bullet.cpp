#include "../../libOne/inc/libOne.h"
#include "bullet.h"

namespace GAME04 {
    extern float scrollX;

    void BULLET::shoot(float x, float y) {
        wx = x; wy = y; hp = 1;
    }

    void BULLET::move() {
        if (hp <= 0) return;
        wx += vx;
        if (wx > scrollX + 2000) hp = 0;
    }

    void BULLET::draw()
    {
        if (hp > 0)
            circle(wx - scrollX, wy, pr);
    }
}