#include "../../libOne/inc/libOne.h"
#include "../MAIN/MAIN.h"
#include "GAME06.h"
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <string>
#include <windows.h>

// マウス左クリックを検出する関数
bool isMouseLeftPressed() {
    return (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0;
}

// マウスX座標取得
int getMouseX() {
    POINT p;
    GetCursorPos(&p);
    ScreenToClient(GetForegroundWindow(), &p);
    return p.x;
}

// マウスY座標取得
int getMouseY() {
    POINT p;
    GetCursorPos(&p);
    ScreenToClient(GetForegroundWindow(), &p);
    return p.y;
}

using namespace std::chrono;

namespace GAME06 {

    static int circleX, circleY;
    static int score = 0;
    static const int RADIUS = 50;
    static long long lastUpdateTime = 0;
    // ゲーム開始時間
    static long long startTime = 0;
    // 制限時間
    static const int TIME_LIMIT_MS = 60000;

    int GAME::create() {
        srand((unsigned int)time(nullptr));

        // 初期位置
        circleX = rand() % (1920 - 2 * RADIUS) + RADIUS;
        circleY = rand() % (1080 - 2 * RADIUS) + RADIUS;

        // 現在時刻
        lastUpdateTime = duration_cast<milliseconds>(
            steady_clock::now().time_since_epoch()).count();

        // ゲーム開始時間
        startTime = lastUpdateTime;

        return 0;
    }

    void GAME::destroy() {
        
    }

    void GAME::proc() {
        // 背景色
        clear(30, 30, 60); 

        // 現在時刻
        long long currentTime = duration_cast<milliseconds>(
            steady_clock::now().time_since_epoch()).count();

        // 経過時間
        long long elapsed = currentTime - startTime;

        // 残り時間
        int remainingTime = max(0, (TIME_LIMIT_MS - (int)elapsed) / 1000);

        // スコア表示
        fill(255);
        textSize(32);
        text((std::string("スコア: ") + std::to_string(score)).c_str(), 50, 50);

        // 残り時間表示
        text((std::string("残り時間: ") + std::to_string(remainingTime) + "秒").c_str(), 50, 90);

        // 制限時間を超えたら終了
        if (elapsed >= TIME_LIMIT_MS) {
            fill(255, 0, 0);
            textSize(60);
            text("TIME UP!", 700, 500);
            return; 
        }

        // 1秒ごとに円を移動
        if (currentTime - lastUpdateTime > 1000) {
            circleX = rand() % (1920 - 2 * RADIUS) + RADIUS;
            circleY = rand() % (1080 - 2 * RADIUS) + RADIUS;
            lastUpdateTime = currentTime;
        }

        // 円
        fill(0, 255, 0);
        circle((float)circleX, (float)circleY, (float)RADIUS);

        // マウスクリックで円に当たったらスコア加算
        if (isMouseLeftPressed()) {
            int mx = getMouseX();
            int my = getMouseY();
            int dx = mx - circleX;
            int dy = my - circleY;
            if (dx * dx + dy * dy <= RADIUS * RADIUS) {
                score++;
                circleX = rand() % (1920 - 2 * RADIUS) + RADIUS;
                circleY = rand() % (1080 - 2 * RADIUS) + RADIUS;
            }
        }
    }
}
