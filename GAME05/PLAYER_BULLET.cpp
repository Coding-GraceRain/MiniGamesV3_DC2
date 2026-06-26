#include"../../libOne/inc/window.h"
#include"ANIM.h"
#include"CONTAINER.h"
#include"GAME.h"
#include"MAP.h"
#include "PLAYER_BULLET.h"
namespace GAME05 {
    void PLAYER_BULLET::create() {//
        Chara = game()->container()->data().playerBulletChara;
    }
    void PLAYER_BULLET::appear(float wx, float wy, float vx, float vy) {
        Chara.hp = game()->container()->data().playerBulletChara.hp;
        Chara.wx = wx;
        Chara.wy = wy;
        Chara.vx = vx;
        Chara.vy = vy;

        Chara.angle = 0.0f;
    }
    void PLAYER_BULLET::update() {
        //移動--------------------------------------------------------------------------
        Chara.wx += Chara.vx * (Chara.speed * delta);

        if (Chara.vx > 0)
        {
            // 時計回りに回転
            Chara.angle += 360.0f * delta;
        }
        else
        {
        // 左向きの弾なら反時計回り
            Chara.angle -= 360.0f * delta;
        }


        //マップ------------------------------------------------------------------------
        // 弾が、マップチップに当たった、または、ウィンドウの外に出た
        if (game()->map()->collisionCharaRect(wLeft(), wTop(), wRight(), wBottom()) ||
            Chara.wx < game()->map()->wDispLeft() ||
            Chara.wx > game()->map()->wDispRight()) {
            Chara.hp = 0;
        }
    }
}