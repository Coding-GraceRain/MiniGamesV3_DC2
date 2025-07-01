#include "../../libOne/inc/libOne.h"
#include "../MAIN/MAIN.h"
#include "GAME00.h"
#include <string> 

namespace GAME00 {

    int GAME::create() {
        state = STATE_TITLE;
        playerX = 640;
        playerY = 900;
        bulletTimer = 0;
        spawnTimer = 0;
        playerHP = 10;
        enemyShotTimer = 0;
        killPoint = 0;
        enemies.clear();
        bullets.clear();
        enemyBullets.clear();
        return 0;
    }

    void GAME::destroy() {
        // 今は何もしない
    }

    void GAME::proc() {
        const float PLAYER_RADIUS = 20.0f;
        bool allEnemiesDead = true;
        std::string hpText;

        clear(0, 0, 100);

        switch (state) {
        case STATE_TITLE:
            textSize(150);
            fill(255, 255, 100);
            text("弾幕ゲーム", 300, 300);
            fill(255);
            textSize(50);
            text("Press SPACE to Start", 300, 380);
            if (isTrigger(KEY_SPACE)) {
                state = STATE_INSTRUCTIONS;  // 👈 まず操作説明へ
            }
            fill(255);
            text("Press ENTER to return to Menu", 300, 480);
            if (isTrigger(KEY_ENTER)) {
                main()->backToMenu();
            }
            break;

        case STATE_INSTRUCTIONS:
            textSize(40);
            fill(255);
            text("操作説明:", 300, 200);
            text("十字キーで動けます", 300, 260);
            text("弾はCキーで打てます　チャージショットもありますが空気です", 300, 320);
            text("一分半ほど耐えきればステージクリアです！", 300, 380);
            fill(255, 255, 0);
            text("Press ENTER to Begin! good luck!", 300, 480);
            if (isTrigger(KEY_ENTER)) {
                state = STATE_PLAY;
                bulletTimer = 0;
                spawnTimer = 0;
                playerHP = 10;
                enemies.clear();
                bullets.clear();
                enemyBullets.clear();
                playerX = 640;
                playerY = 900;
                killPoint = 0;
            }
            break;

        case STATE_PLAY: {
            // {}で囲って変数スコープ確保
            text(spawnTimer, 300, 200);
            if (isPress(KEY_LEFT))  playerX -= playerSpeed;
            if (isPress(KEY_RIGHT)) playerX += playerSpeed;
            if (isPress(KEY_UP))    playerY -= playerSpeed;
            if (isPress(KEY_DOWN))  playerY += playerSpeed;

            if (playerX < PLAYER_RADIUS) playerX = PLAYER_RADIUS;
            if (playerX > 1920 - PLAYER_RADIUS) playerX = 1920 - PLAYER_RADIUS;
            if (playerY < PLAYER_RADIUS) playerY = PLAYER_RADIUS;
            if (playerY > 1080 - PLAYER_RADIUS) playerY = 1080 - PLAYER_RADIUS;

            fill(255, 255, 255);
            rect(playerX - PLAYER_RADIUS, playerY - PLAYER_RADIUS, 40, 40);

            fill(255);
            textSize(30);
            hpText = "HP: " + std::to_string(playerHP);
            text(hpText.c_str(), 20, 40);

            // プレイヤーHPバー表示（右下）
            float hpBarMaxWidth = 200.0f;
            float hpBarHeight = 20.0f;
            float hpBarX = 1920 - hpBarMaxWidth - 40;
            float hpBarY = 1080 - hpBarHeight - 40;
            // チャージゲージ表示
            float chargeBarMaxWidth = 200.0f;
            float chargeBarHeight = 10.0f;
            float chargeBarX = 1920 - chargeBarMaxWidth - 40;
            float chargeBarY = 1080 - hpBarHeight - 40 - 20;  // HPバーの上に少し間を空けて描画

            // 背景バー
            fill(0);
            rect(chargeBarX, chargeBarY, chargeBarMaxWidth, chargeBarHeight);

            // チャージ比率
            float chargeRatio = (float)chargeTime / CHARGE_THRESHOLD;
            if (chargeRatio > 1.0f) chargeRatio = 1.0f;

            // 色（完了前は青→緑→黄、完了後は赤）
            if (chargeRatio < 0.5f) fill(0, 200, 255);
            else if (chargeRatio < 0.9f) fill(0, 255, 0);
            else if (chargeRatio < 1.0f) fill(255, 255, 0);
            else fill(255, 50, 50);

            // 前景バー（現在のチャージ量）
            rect(chargeBarX, chargeBarY, chargeBarMaxWidth * chargeRatio, chargeBarHeight);

            // チャージショットエフェクト（Cキー長押し時）
            if (isCharging) {
                float scale = 0.8f + 0.4f * sin(chargeTime * 0.1f); // 揺れ演出
                float radius = 30.0f + chargeTime * 0.2f;

                if (chargeTime >= CHARGE_THRESHOLD) {
                    fill(255, 100, 100, 128); // チャージ完了：赤系半透明
                }
                else {
                    fill(100, 255, 255, 100); // チャージ中：水色系
                }
                circle(playerX, playerY, radius * scale);  // 揺れ円
            }

            float hpRatio = playerHP / 10.0f;
            if (hpRatio < 0) hpRatio = 0;
            if (hpRatio > 1) hpRatio = 1;

            fill(0, 0, 0);
            rect(hpBarX, hpBarY, hpBarMaxWidth, hpBarHeight);

            if (hpRatio > 0.5f) {
                fill(0, 255, 0);
            }
            else if (hpRatio > 0.2f) {
                fill(255, 255, 0);
            }
            else {
                fill(255, 0, 0);
            }

            rect(hpBarX, hpBarY, hpBarMaxWidth * hpRatio, hpBarHeight);


            for (auto& b : bullets) {
                b.x += b.vx;
                b.y += b.vy;
                if (b.isCharged) {
                    fill(255, 100, 255);  // 紫っぽい
                    rect(b.x - 6, b.y - 30, 12, 60);
                }
                else {
                    fill(0, 255, 255);
                    rect(b.x - 2, b.y - 10, 4, 20);
                }
            }

            // チャージショット判定
            if (isPress(KEY_C)) {
                if (!isCharging) {
                    chargeTime = 0;
                    isCharging = true;
                }
                chargeTime++;
            }
            else if (isCharging) {
                // Cキーを離したとき
                isCharging = false;
                if (chargeTime >= CHARGE_THRESHOLD) {
                    // チャージ完了 → 強弾発射
                    bullets.push_back({ playerX, playerY, 0.0f, -10.0f, true });
                }
                else {
                    // チャージ足りない → 通常弾5連射
                    for (int i = 0; i < 5; i++) {
                        float angle = -90 + (i - 2) * 10;
                        float rad = angle * 3.14159f / 180.0f;
                        float vx = cos(rad) * 6.0f;
                        float vy = sin(rad) * 6.0f;
                        bullets.push_back({ playerX, playerY, vx, vy, false });
                    }
                }
            }

            spawnTimer++;
                if (spawnTimer == 30) {
                    enemies.clear();
                        enemies.push_back({ 50, 100, 1.0f, 0.0f, true ,3 });
                        enemies.push_back({ 50, 200, 1.5f, 0.0f, true ,3 });
                        enemies.push_back({ 50, 300, 2.0f, 0.0f, true ,3 });
                        enemies.push_back({ 1870, 300, -2.0f, 0.0f, true ,3 });
                        enemies.push_back({ 1870, 400, -1.5f, 0.0f, true ,3 });
                        enemies.push_back({ 1870, 500, -1.0f, 0.0f, true ,3 });
                }
                if (spawnTimer >= 300 && spawnTimer <= 1000) {
                    if (spawnTimer % 200 == 0) {
                        float x = (rand() % 1800) + 60;
                        float y = (rand() % 100) + 10;
                        float vx = (rand() % 1) + 0.5f;
                        float vy = (rand() % 1) + 0.5f;
                        enemies.push_back({ x, y, vx, 0, true , 3 });
                    }
                }
                if (spawnTimer > 1000 && spawnTimer <= 2000) {
                    if (spawnTimer % 175 == 0) {
                        float x = (rand() % 1800) + 60;
                        float y = (rand() % 110) + 10;
                        float vx = (rand() % 3) + 0.5f;
                        float vy = (rand() % 3) + 0.5;
                        enemies.push_back({ x, y, vx, 0, true , 3 });
                    }
                }
                if (spawnTimer > 2000 && spawnTimer <= 3000) {
                    if (spawnTimer % 150 == 0) {
                        float x = (rand() % 1800) + 60;
                        float y = (rand() % 150) + 10;
                        float vx = (rand() % 3) + 0.5f;
                        float vy = (rand() % 3) + 0.5;
                        enemies.push_back({ x, y, vx, 0, true , 3 });
                    }
                }
                if (spawnTimer > 3000 && spawnTimer <= 4000) {
                    if (spawnTimer % 125 == 0) {
                        float x = (rand() % 1800) + 60;
                        float y = (rand() % 200) + 10;
                        float vx = (rand() % 2) + 0.5f;
                        float vy = (rand() % 2) + 0.5f;
                        enemies.push_back({ x, y, vx, 0, true , 3 });
                    }
                }
                if (spawnTimer > 4000 && spawnTimer <= 5000) {
                    if (spawnTimer % 75 == 0) {
                        float x = (rand() % 1800) + 60;
                        float y = (rand() % 300) + 10;
                        float vx = (rand() % 3) + 0.5f;
                        float vy = (rand() % 3) + 0.5f;
                        enemies.push_back({ x, y, vx, 0, true , 3 });
                    }
                }

            for (auto& e : enemies) {
                if (!e.alive) continue;

                e.x += e.vx;
                e.y += e.vy;

                // 横端で跳ね返る処理（画面端 0 ～ 1920）
                if (e.x < 0 || e.x > 1920) {
                    e.vx *= -1;
                    e.x += e.vx; // はみ出し修正
                }

                // 下まで行ったら上から出す（1080が画面下）
                if (e.y > 1080) {
                    e.y = -40; // 画面上に戻す（敵のサイズ分オフセット）
                }

                fill(255, 0, 0);
                rect(e.x - 20, e.y - 20, 40, 40);
            }

            enemyShotTimer++;
            if (enemyShotTimer >= 300) {
                enemyShotTimer = 0;
                for (auto& e : enemies) {
                    if (!e.alive) continue;
                    for (int i = -1; i <= 16; i++) {
                        float angle = 90 + i * 20;
                        float rad = angle * 3.14159f / 180.0f;
                        float vx = cos(rad);
                        float vy = sin(rad);
                        enemyBullets.push_back({ e.x, e.y, vx, vy, true });
                    }
                }
            }

            for (auto& e : enemies) {
                if (!e.alive) continue;

                float barWidth = 40.0f;
                float barHeight = 6.0f;
                float hpRatio = (float)e.hp / 3.0f;

                fill(0, 0, 0);
                rect(e.x - barWidth / 2, e.y + 25, barWidth, barHeight);

                if (e.hp == 3) fill(0, 255, 0);
                else if (e.hp == 2) fill(255, 255, 0);
                else if (e.hp == 1) fill(255, 0, 0);

                rect(e.x - barWidth / 2, e.y + 25, barWidth * hpRatio, barHeight);
            }

            for (auto& eb : enemyBullets) {
                if (!eb.active) continue;
                eb.x += eb.vx;
                eb.y += eb.vy;
                fill(255, 128, 0);
                circle(eb.x, eb.y, 10);
            }

            // 敵との当たり判定（敵に当たったらHP1減らす）
            for (auto& e : enemies) {
                if (!e.alive) continue;
                float dx = e.x - playerX;
                float dy = e.y - playerY;
                if (dx * dx + dy * dy < (20 + 20) * (20 + 20)) {
                    playerHP--;        // HP1減る
                    e.alive = false;
                    if (playerHP <= 0) {
                        state = STATE_GAME_OVER;
                    }
                }
            }
            for (auto& eb : enemyBullets) {
                if (!eb.active) continue;
                float dx = eb.x - playerX;
                float dy = eb.y - playerY;
                if (dx * dx + dy * dy < (20 + 10) * (20 + 10)) { // 半径20と10
                    eb.active = false;
                    playerHP--;
                    if (playerHP <= 0) {
                        state = STATE_GAME_OVER;
                    }
                }
            }

            enemyBullets.erase(std::remove_if(enemyBullets.begin(), enemyBullets.end(),
                [](const EnemyBullet& b) {
                    return b.x < -20 || b.x > 1940 || b.y < -20 || b.y > 1100;
                }), enemyBullets.end());

            for (auto& e : enemies) {
                if (!e.alive) continue;
                for (auto& b : bullets) {
                    if (abs(b.x - e.x) < 20 && abs(b.y - e.y) < 20) {
                        if (b.isCharged) {
                            e.hp -= 3;  // チャージ弾は一気に3ダメージ
                        }
                        else {
                            e.hp--;
                        }
                        b.y = -9999; // 弾を消す
                        if (e.hp <= 0) {
                            killPoint++;
                            e.alive = false;
                        }
                    }
                }

            }
            if (spawnTimer == 5000) {
                spawnTimer = 0;
                state = STATE_CLEAR;
            }

            bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
                [](const Bullet& b) {
                    return b.y < -20 || b.x < -20 || b.x > 1940;
                }), bullets.end());

            if (playerY < 0 || playerY > 1080 || playerX < 0 || playerX > 1920) {
                state = STATE_GAME_OVER;
            }

        }
                       break;

        case STATE_GAME_OVER:
            textSize(50);
            fill(255, 0, 0);
            text("GAME OVER", 400, 400);
            fill(255);
            text("Press ENTER to return to Menu", 300, 480);
            if (isTrigger(KEY_ENTER)) {
                main()->backToMenu();
            }
            break;

        case STATE_CLEAR:
            textSize(150);
            fill(0, 255, 0);
            text("CLEAR! 君は生き残った！", 50, 300);
            textSize(50);
            fill(0, 255, 0);
            text("倒したエネミー", 300, 700);
            fill(0, 255, 0);
            text(killPoint, 700, 700);
            fill(0, 255, 0);
            text("残ったHP", 300, 900);
            fill(0, 255, 0);
            text(playerHP, 700, 900);
            fill(255);
            text("Press ENTER to return to Title", 1000, 980);
            if (isTrigger(KEY_ENTER)) {
                state = STATE_TITLE;
            }
            break;

        }

    }
}
