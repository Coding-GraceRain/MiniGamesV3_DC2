#pragma once
#include "CHARACTER.h"
namespace GAME05 {
    class SURAIMU :
        public CHARACTER
    {
    public:
        struct DATA {
            int   rightAnimId = 0;//右向きのアニメーションID
            int   leftAnimId = 1;//左向きのアニメーションID
            int   fallFlag = 0;//落下フラグ
            float curWx = 0;//現在のワールドX座標
            float initVecX = 0;//初期速度X
            float initVecY = 0;//初期速度Y
            float gravity = 0;//重力
            float alphaLowVal = 0;//アルファの低値
            float damageTime = 0;//ダメージ時間
            float damageInterval = 0;//ダメージ間隔
            char explosionCharaId = 0;//爆発キャラクターID
        };
    private:
        DATA Suraimu;//スライムのデータ
    public:
        SURAIMU(class GAME_* game) :CHARACTER(game) {}
        void create();
        void appear(float wx, float wy, float vx, float vy);
        void update();
    private:
        void Move();
        void CollisionWithMap();
    
        void damage();
    };
}