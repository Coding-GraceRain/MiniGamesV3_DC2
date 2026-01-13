#include "../../libOne/inc/libOne.h"
#include "player.h"

namespace GAME04 {

    extern float scrollX;

    void PLAYER::move()
    {
        // 横移動
        if (isPress(KEY_D)) vx = 5;
        else if (isPress(KEY_A)) vx = -5;
        else vx = 0;

        // ジャンプ
        if (isTrigger(KEY_W) && onGround) {
            vy = -18;
            onGround = false;
        }

        // 重力
        vy += 1.2f;

        // 移動
        wx += vx;
        wy += vy;

        // 地面
        if (wy > 800) {
            wy = 800;
            vy = 0;
            onGround = true;
        }

        // カメラ追従（画面中央）
        scrollX = wx - 400;
        if (scrollX < 0) scrollX = 0;
    }

    void PLAYER::draw()
    {
        circle(wx - scrollX, wy, pr);
    }
}