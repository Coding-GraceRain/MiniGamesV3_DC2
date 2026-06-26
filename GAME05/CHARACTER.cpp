#include"../../libOne/inc/graphic.h"
#include"ANIMS.h"
#include"CONTAINER.h"
#include"GAME.h"
#include"MAP.h"
#include"CHARACTER.h"
namespace GAME05 {
    CHARACTER::CHARACTER(GAME_* game) :
        GAME_OBJECT(game) {}//コンストラクタ
    void CHARACTER::create() {}//キャラの初期設定を行う関数
    void CHARACTER::init() {//キャラの初期化を行う関数
        Chara.hp = 0;
    }
    void CHARACTER::appear(float wx, float wy, float vx, float vy) {//キャラを出現させる関数
        Chara.wx = wx;
        Chara.wy = wy;
        Chara.hp = 1;
    }
    void CHARACTER::update() {//キャラの更新を行う関数
        float px = Chara.wx - game()->map()->wx();//ワールド座標を画面座標へ変換
        if (px < -game()->map()->chipSize()) {//画面の左へ完全に出たら消す
            Chara.hp = 0;
        }
    }
    void CHARACTER::draw() {//キャラの描画を行う関数
        imageColor(Chara.color);//画像の色を設定
        float px = Chara.wx - game()->map()->wx();//ワールド座標→画面座標へ変換
        float py = Chara.wy - game()->map()->wy();//ワールド座標→画面座標へ変換
        if (Chara.anims) {//複数アニメーション
            Chara.anims->anim(Chara.animId)->draw(&Chara.animData,
                px, py, Chara.angle, Chara.scale);
        }
        else if (Chara.anim) {//アニメーション
            Chara.anim->draw(&Chara.animData,
                px, py, Chara.angle, Chara.scale);
        }
        else {//普通の画像
            image(Chara.img, px, py, Chara.angle, Chara.scale);
        }
    }
    void CHARACTER::damage() {//キャラがダメージを受けるときの関数
        if (Chara.hp > 0) {
            Chara.hp--;
        }
    }
}