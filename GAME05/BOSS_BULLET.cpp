#include"../../libOne/inc/window.h"
#include <cmath>
#include"ANIM.h"
#include"CONTAINER.h"
#include"GAME.h"
#include"MAP.h"
#include "BOSS_BULLET.h"
namespace GAME05 {
    void BOSS_BULLET::create() {
        Chara = game()->container()->data().bossBulletChara;
        
    }
    void BOSS_BULLET::appear(float wx, float wy, float vx, float vy) {
        Chara.hp = game()->container()->data().bossBulletChara.hp;
        Chara.wx = wx;
        Chara.wy = wy;
        Chara.vx = vx;
        Chara.vy = vy;

        float angle = atan2f(Chara.vy, Chara.vx);
    }
    void BOSS_BULLET::update() {
        //移動--------------------------------------------------------------------------
        Chara.wx += Chara.vx * Chara.speed * delta;
        Chara.wy += Chara.vy * Chara.speed * delta;
        //マップ------------------------------------------------------------------------
        // 弾が、マップチップに当たった、または、ウィンドウの外に出た
        if (game()->map()->collisionCharaRect(wLeft(), wTop(), wRight(), wBottom()) ||
            Chara.wx < game()->map()->wDispLeft() ||
            Chara.wx > game()->map()->wDispRight()) {
            Chara.hp = 0;
        }
    }
}
