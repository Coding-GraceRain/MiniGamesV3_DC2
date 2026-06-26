#include "TURRETS.h"
#include "GAME03.h"
#include "CONTAINER.h"

namespace GAME03
{
    TURRETS::TURRETS(class GAME* game):
    CHARACTER(game){
    }
    TURRETS::~TURRETS(){
    }
    void TURRETS::create(){
        Chara = game()->container()->data().turretChara;
        Turret = game()->container()->data().turret;
    }
    void TURRETS::appear(float x, float y, float vx, float vy) {
        Chara.hp = game()->container()->data().turretChara.hp;
        Chara.x = x;
        Chara.y = y;
        Turret.triggerCnt = game()->container()->data().turret.triggerCnt;
    }
    void TURRETS::update(){
        Turret.elapsedTime += delta;
        if (Turret.elapsedTime >= Turret.interval) {
            Turret.elapsedTime -= Turret.interval;
            ++Turret.triggerCnt %= Turret.triggerInterval;
            if (Turret.triggerCnt == Turret.trigger1st ||
                Turret.triggerCnt == Turret.trigger2nd ||
                Turret.triggerCnt == Turret.trigger3rd ||
                Turret.triggerCnt == Turret.trigger4th) {
                game()->characterManager()->appear(Turret.bulletCharaId,
                    Chara.x + Turret.bulletOffsetX, Chara.y + Turret.bulletOffsetY, 0, 1);
            }
        }
    }
}