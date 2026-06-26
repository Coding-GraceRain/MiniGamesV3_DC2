#include"../../libOne/inc/window.h"
#include <cmath>
#include"ANIM.h"
#include"CONTAINER.h"
#include"GAME.h"
#include"MAP.h"
#include "BOSS.h"
namespace GAME05 {
    void BOSS::create() {
        Chara = game()->container()->data().bossChara;
        Boss = game()->container()->data().boss;
    }
    void BOSS::appear(float wx, float wy, float vx, float vy) {
        Chara.hp = game()->container()->data().bossChara.hp;
        Chara.wx = wx;
        Chara.wy = wy;

        Boss.moveStartX = wx;
        Boss.moveStartY = wy;
        Boss.moveState = 0;
        Boss.triggerCnt = game()->container()->data().boss.triggerCnt;
        
    }
   
    void BOSS::update() {
        Move();
        //ボス弾発射----------------------------------------------------------------
        Boss.elapsedTime += delta;
        if (Boss.elapsedTime >= Boss.interval) {
            Boss.elapsedTime -= Boss.interval;
            ++Boss.triggerCnt %= Boss.triggerInterval;
            if (Boss.triggerCnt == Boss.trigger1st ||
                Boss.triggerCnt == Boss.trigger2nd ||
                Boss.triggerCnt == Boss.trigger3rd ||
                Boss.triggerCnt == Boss.trigger4th ||
                Boss.triggerCnt == Boss.trigger5nd ||
                Boss.triggerCnt == Boss.trigger6rd ||
                Boss.triggerCnt == Boss.trigger7th)  {
                float bx = Chara.wx - Boss.bulletOffsetX;
                float by = Chara.wy + 134;

                PLAYER* player = game()->characterManager()->player();

                float dx = player->wx() - bx;
                float dy = player->wy() - by;

                float len = sqrtf(dx * dx + dy * dy);

                dx /= len;
                dy /= len;

                Chara.vx = dx;
                Chara.vy = dy;

                game()->characterManager()->appear(
                    Boss.bulletCharaId,
                    bx,
                    by,
                    dx,
                    dy
                );
            }
        }
        //マップ------------------------------------------------------------------------
        // ウィンドウの外に出た
        if (Chara.wx < game()->map()->wDispLeft()) {
            Chara.hp = 0;
        }
    }
    void BOSS::Move() {//ボスの移動を行う関数
        const float speed = 100.0f;

        switch (Boss.moveState) {

        case 0: // 右へ300
            Chara.wx += speed * delta;

            if (Chara.wx >= Boss.moveStartX + 300) {
                Chara.wx = Boss.moveStartX + 300;
                Boss.moveState = 1;
            }
            break;

        case 1: // 下へ300
            Chara.wy += speed * delta;

            if (Chara.wy >= Boss.moveStartY + 300) {
                Chara.wy = Boss.moveStartY + 300;
                Boss.moveState = 2;
            }
            break;

        case 2: // 左へ300
            Chara.wx -= speed * delta;

            if (Chara.wx <= Boss.moveStartX) {
                Chara.wx = Boss.moveStartX;
                Boss.moveState = 3;
            }
            break;

        case 3: // 上へ400
            Chara.wy -= speed * delta;

            if (Chara.wy <= Boss.moveStartY-100) {
                Chara.wy = Boss.moveStartY-100;
                Boss.moveState = 4;
            }
            break;

        case 4: // 右へ300
            Chara.wx += speed * delta;

            if (Chara.wx >= Boss.moveStartX + 300) {
                Chara.wx = Boss.moveStartX + 300;
                Boss.moveState = 5;
            }
            break;

        case 5: // 下へ300
            Chara.wy += speed * delta;

            if (Chara.wy >= Boss.moveStartY + 200) {
                Chara.wy = Boss.moveStartY + 200;
                Boss.moveState = 6;
            }
            break;

        case 6: // 左へ300
            Chara.wx -= speed * delta;

            if (Chara.wx <= Boss.moveStartX) {
                Chara.wx = Boss.moveStartX;
                Boss.moveState = 7;
            }
            break;

        case 7: // 上へ300
            Chara.wy -= speed * delta;

            if (Chara.wy <= Boss.moveStartY - 100) {
                Chara.wy = Boss.moveStartY - 100;
                Boss.moveState = 8;
            }
            break;

        case 8: // 右へ300
            Chara.wx += speed * delta;

            if (Chara.wx >= Boss.moveStartX + 300) {
                Chara.wx = Boss.moveStartX + 300;
                Boss.moveState = 9;
            }
            break;

        case 9: // 下へ500
            Chara.wy += speed * delta;

            if (Chara.wy >= Boss.moveStartY + 300) {
                Chara.wy = Boss.moveStartY + 300;
                Boss.moveState = 10;
            }
            break;

        case 10: // 左へ300
            Chara.wx -= speed * delta;

            if (Chara.wx <= Boss.moveStartX) {
                Chara.wx = Boss.moveStartX;
                Boss.moveState = 11;
            }
            break;

        case 11: // 上へ300
            Chara.wy -= speed * delta;

            if (Chara.wy <= Boss.moveStartY) {
                Chara.wy = Boss.moveStartY;
                Boss.moveState = 0;
            }
            break;
        }
    }
    void BOSS::damage() {
        if (Chara.hp > 0) {
            Boss.damageTime = Boss.damageInterval;
            Chara.hp--;
            if (Chara.hp == 0) {
                game()->characterManager()->appear(Boss.explosionCharaId,
                    Chara.wx, Chara.wy);
            }
        }
    }
}