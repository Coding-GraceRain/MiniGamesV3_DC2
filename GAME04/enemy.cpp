#include "../../libOne/inc/libOne.h"
#include "enemy.h"

namespace GAME04 {
   

    extern float scrollX;

    void ENEMY::move()
    {
        
    }

    void ENEMY::draw()
    {
        if (active)
            circle(wx - scrollX, wy, pr);
    }
}