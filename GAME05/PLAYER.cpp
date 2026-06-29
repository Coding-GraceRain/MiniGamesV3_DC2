#include"../../libOne/inc/window.h"
#include"../../libOne/inc/input.h"
#include"../../libOne/inc/graphic.h"
#include"ANIMS.h"
#include"CONTAINER.h"
#include"GAME.h"
#include"MAP.h"
#include "PLAYER.h"
namespace GAME05 {
    void PLAYER::create() {//プレイヤーの初期設定を行う関数
        Chara = game()->container()->data().playerChara;
        Player = game()->container()->data().player;
    }
    void PLAYER::appear(float wx, float wy, float vx, float vy) {//プレイヤーを出現させる関数
        Chara.hp = game()->container()->data().playerChara.hp;
        Chara.wx = wx;
        Chara.wy = wy;
        Chara.animId = Player.rightAnimId;
        Player.jumpFlag = 0;
        State = STATE::STRUGGLING;
    }
    void PLAYER::update() {//プレイヤーの更新を行う関数
        Launch();
        Move();
        CollisionWithMap();
        CheckState();
    }
    void PLAYER::Launch() {
        //弾発射
        if (isTrigger(KEY_L)) {
            float vx = 1.0f;
            if (Chara.animId == Player.leftAnimId) vx = -1.0f;
            float wx = Chara.wx + Player.bulletOffsetX * vx;
            float wy = Chara.wy+20;
            game()->characterManager()->appear(Player.bulletCharaId, wx, wy, vx);
        }
    }
    void PLAYER::Move() {//プレイヤーの移動を行う関数
        //ジャンプ
        if (Player.jumpFlag == 0 && isTrigger(KEY_J)) {
            Chara.vy = Player.initVecUp;
            Player.jumpFlag = 1;
        }
        if (Player.jumpFlag == 1) {
            Chara.vy += Player.gravity * delta;
            Chara.wy += Chara.vy * 60 * delta;
        }
        //左右移動
        //  移動ベクトルを決定
        Chara.vx = 0.0f;
        if (isPress(KEY_A)) {
            Chara.vx = -Chara.speed * delta;
            Chara.animId = Player.leftAnimId;
        }
        if (isPress(KEY_D)) {
            Chara.vx = Chara.speed * delta;
            Chara.animId = Player.rightAnimId;
        }
        //  移動前に現在のChara.wxをPlayer.curWxにとっておく
        Player.curWx = Chara.wx;
        //  移動
        if (Chara.vx != 0.0f) {//左右キー入力あり
            //とりあえず「次に移動する予定」の位置としてChara.wxを更新しておき
            //あとで、マップに食い込んでいたら、元のPlayer.curWxに戻す
            Chara.wx += Chara.vx;
        }
        else {//左右キー入力がないとき
            Chara.animData.imgIdx = 0;
            Chara.animData.elapsedTime = -delta;
        }
    }
    void PLAYER::CollisionWithMap() {//マップとの衝突判定を行う関数
        MAP* map = game()->map();
        // マップチップとキャラの右
        if (Chara.animId == Player.rightAnimId) {
            if (map->collisionCharaRight(Chara.wx, Chara.wy)) {
                //移動予定位置がマップに食い込んでいるので現在の位置に戻す
                Chara.wx = Player.curWx;
            }
        }
        // マップチップとキャラの左
        else {
            if (map->collisionCharaLeft(Chara.wx, Chara.wy) ||
                Chara.wx < map->wx() //または、ウィンドウの左にぶつかったか
                ) {
                Chara.wx = Player.curWx;
            }
        }
        // マップチップとキャラの上
        if (map->collisionCharaTop(Chara.wx, Chara.wy)) {
            Chara.vy = Player.initVecDown;//落ちていく初速度
        }
        // マップチップとキャラの下
        if (map->collisionCharaBottom(Player.curWx, Chara.wy)) {
            //--「マップチップに食い込んでいる」
            // または「上に立っているとき」もここを通る--
            //ジャンプ（落下）処理の停止
            Player.jumpFlag = 0;
            Chara.vy = 0.0f;
            //強制的に上に立っている位置にする
            Chara.wy = (int)Chara.wy / map->chipSize() * (float)map->chipSize();
        }
        else {
            Player.jumpFlag = 1;//落ちてくトリガー。このフラッグを立てるだけで落ちていく。
        }
    }
    void PLAYER::CheckState() {//プレイヤーの状態をチェックする関数
        //画面の下に落ちた
        if (Chara.wy > height + game()->map()->chipSize()) {
            State = STATE::FALL;
            Chara.hp = 0;
            return;
        }
        //ステージクリアした
        if (Chara.wx > game()->map()->wDispRight()) {
            State = STATE::SURVIVED;
            Chara.hp = 0;
        }
    }
    void PLAYER::damage() {//プレイヤーにダメージを与える関数
        if (Chara.hp > 0) {
            Chara.hp--;
            if (Chara.hp == 0) {
                State = STATE::DIED;
                Chara.vy = Player.initVecUp;//はね始めのトリガー
            }
        }
    }
    bool PLAYER::died() {//プレイヤーが死亡したかチェックする関数
        if (State == STATE::DIED) {
            Chara.vy += Player.gravity * delta;
            Chara.wy += Chara.vy * 60 * delta;
            draw();
            return true;
        }
        else if (State == STATE::FALL) {
            return true;
        }
        return false;
    }
    bool PLAYER::survived() {//プレイヤーが生存したかチェックする関数
        return State == STATE::SURVIVED;
    }
    float PLAYER::overCenterVx() {//センターを越えた水平方向の速度を求める
        //マップをスクロールさせるためのベクトルを求める
        float centerWx = (game()->map()->wx() + width / 2 - game()->map()->chipSize() / 2);
        float overCenterVx = Chara.wx - centerWx;
        if (overCenterVx < 0 || Chara.hp == 0)overCenterVx = 0;
        return overCenterVx;
    }
}