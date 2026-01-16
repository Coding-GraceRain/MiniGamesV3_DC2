#include "../../libOne/inc/libOne.h"
#include "enemy.h"

namespace GAME04 {
   

    extern float scrollX;

    void ENEMY::move()
    {
        if (!active) return;

        wx += vx;
    }

    void ENEMY::draw()
    {
        if (!active) return;
        circle(wx - scrollX, wy, pr);
       /* if (active)
            circle(wx - scrollX, wy, pr);*/
    }
}