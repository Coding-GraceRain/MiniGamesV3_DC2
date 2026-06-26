#include"../../libOne/inc/window.h"
#include"ANIM.h"
#include"CONTAINER.h"
#include"GAME.h"
#include"GAME05.h"
#include"MAP.h"
#include"SURAIMU.h"
namespace GAME05 {
    void SURAIMU::create() {//スライムの初期設定を行う関数
        Chara = game()->container()->data().suraimuChara;
        Suraimu = game()->container()->data().suraimu;
    }
    void SURAIMU::appear(float wx, float wy, float vx, float vy) {//スライムを出現させる関数
        Chara.hp = game()->container()->data().suraimuChara.hp;
        Chara.wx = wx;
        Chara.wy = wy;
        Chara.vx = Suraimu.initVecX;
        Chara.vy = Suraimu.initVecY;
        Chara.animId = Suraimu.leftAnimId;
        Suraimu.damageTime = 0;
        Suraimu.fallFlag = 0;
    }
    void SURAIMU::update() {//スライムの更新を行う関数
        Move();
        CollisionWithMap();
     
    }
    void SURAIMU::Move() {//スライムの移動を行う関数
        //落下
        if (Suraimu.fallFlag) {
            Chara.vy += Suraimu.gravity * delta;
            Chara.wy += Chara.vy * 60 * delta;
        }
        //現在の位置をとっておく
        Suraimu.curWx = Chara.wx;
        //左右にうごく
        Chara.wx += Chara.vx * (Chara.speed * delta);
    }
    void SURAIMU::CollisionWithMap() {//スライムとマップの衝突判定を行う関数
        MAP* map = game()->map();
        // マップチップにぶつかったら向きを変える
        if (Suraimu.fallFlag == 0) {
            if (map->collisionCharaLeft(Chara.wx+30, Chara.wy) ||
                map->collisionCharaRight(Chara.wx-30, Chara.wy)) {
                Chara.animId = 1 - Chara.animId;
                Chara.vx = -Chara.vx;
                Chara.wx = Suraimu.curWx;
            }
        }
        // 接地チェック（キャラの下にマップチップがあるかどうか）
        if (map->collisionCharaBottom(Suraimu.curWx, Chara.wy)) {
            //接地または埋まっている
            Suraimu.fallFlag = 0;
            Chara.vy = 0;
            //埋まらないように高さを補正する
            Chara.wy = (int)Chara.wy / map->chipSize() * (float)map->chipSize();
        }
        else {//接地していない
            Suraimu.fallFlag = 1;//落とす
        }
        // ウィンドウの外に出た
        if (Chara.wx < map->wDispLeft()) {
            Chara.hp = 0;
        }
    }
   
    void SURAIMU::damage() {//スライムがダメージを受けるときの関数
        if (Chara.hp > 0) {
            Suraimu.damageTime = Suraimu.damageInterval;
            Chara.hp--;
            if (Chara.hp == 0) {
                game()->characterManager()->appear(Suraimu.explosionCharaId,
                    Chara.wx, Chara.wy);
            }
        }
    }
}