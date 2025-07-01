#pragma once
#include "../../libOne/inc/libOne.h"
#include "../MAIN/GAME_BASE.h"
#include <vector>
#include <string>

namespace GAME00 {

    struct Bullet {
        float x, y;
        float vx, vy;
        bool isCharged = false;
    };

    struct Enemy {
        float x, y;
        float vx, vy;
        bool alive;
        int hp;
    };

    struct EnemyBullet {
        float x, y;
        float vx, vy;
        bool active;
    };


    class GAME : public GAME_BASE {
    private:
        // プレイヤー
        float playerX = 640, playerY = 900, playerSpeed = 4.0f;
        int playerHP = 10;
        bool prevC = false;
        bool isCharging = false;
        int chargeTime = 0;
        const int CHARGE_THRESHOLD = 90;

        // タイマー&管理
        int bulletTimer = 0, spawnTimer = 0, enemyShotTimer = 0;
        bool bossAppeared = false;
        bool allDead = true;
        int splitCount = 0;
        int killPoint = 0;

        std::vector<Bullet> bullets;
        std::vector<Enemy> enemies;
        std::vector<EnemyBullet> enemyBullets;

        template <typename T>
        constexpr const T& my_clamp(const T& v, const T& lo, const T& hi) {
            return (v < lo) ? lo : (hi < v) ? hi : v;
        }

        enum State {
            STATE_TITLE,
            STATE_INSTRUCTIONS,
            STATE_PLAY,
            STATE_GAME_OVER,
            STATE_CLEAR
        } state = STATE_TITLE;

    public:
        GAME(class MAIN* main) :GAME_BASE(main) {};
        ~GAME() {};
        int create();
        void proc();
        void destroy();
    };

}
