#include "../../libOne/inc/libOne.h"
#include "../MAIN/MAIN.h"
#include "GAME00.h"
#include "Player.h"
#include "CourseManager.h"
#include "CourseData.h"


namespace GAME00 {

    static bool hitRect(float ax, float ay, float aw, float ah,
        float bx, float by, float bw, float bh) {
        return ax < bx + bw && ax + aw > bx && ay < by + bh && ay + ah > by;
    }

    void Player::update(const std::vector<Platform>& platforms) {
        vx = 0;
        if (isPress(KEY_A)) vx = -5;
        if (isPress(KEY_D)) vx = 5;

        if (onGround) coyoteTimer = coyoteTime;
        else coyoteTimer -= 1.0f / 60.0f;

        if (isTrigger(KEY_SPACE)) {
            if (onGround || coyoteTimer > 0) { vy = -10; coyoteTimer = 0; }
            else if (onWall) { vy = -13; vx = (vx == 0) ? 8 : -vx; }
        }

        vy += (vy < 0) ? 0.18f : 0.25f;
        if (vy > 18) vy = 18;

        x += vx; onWall = false;
        for (auto& p : platforms) {
            if (hitRect(x - width / 2, y - height, width, height, p.x, p.y, p.w, p.h)) {
                if (vx > 0) { x = p.x - width / 2; onWall = true; }
                else if (vx < 0) { x = p.x + p.w + width / 2; onWall = true; }
                vx = 0;
            }
        }

        y += vy; onGround = false;
        for (auto& p : platforms) {
            if (hitRect(x - width / 2, y - height, width, height, p.x, p.y, p.w, p.h)) {
                if (vy > 0) { y = p.y; vy = 0; onGround = true; }
                else if (vy < 0) { y = p.y + p.h + height; vy = 0; }
            }
        }
    }

    void Player::draw(float camX, float camY) {
        fill(255, 200, 0);
        rect(x - width / 2 - camX, y - height - camY, width, height);
    }

    int GAME::create() {
        camX = camY = 0;
        startTimer = 0;
        camOffsetY = targetOffsetY = 920;
        isGoal = false; fadeAlpha = 0;
        goalTimer = 0;
        state = GameState::STAGE_SELECT;
        selectedStage = 0;
        return 0;
    }

    void GAME::destroy() {}

    void GAME::updateStageSelect() {
        if (isTrigger(KEY_A)) selectedStage = (selectedStage + 2) % 3;
        if (isTrigger(KEY_D)) selectedStage = (selectedStage + 1) % 3;
        if (isTrigger(KEY_M)) {
            fadeAlpha = 0;
            main()->backToMenu();
        }
        if (isTrigger(KEY_ENTER)) {
            switch (selectedStage) {
            case 0: courseManager.load(COURSE_1, player); break;
            case 1: courseManager.load(COURSE_2, player); break;
            case 2: courseManager.load(COURSE_3, player); break;
            }
            camX = camY = 0;
            camOffsetY = targetOffsetY = 920;
            isGoal = false; fadeAlpha = 0; goalTimer = 0;
            state = GameState::PLAYING;
        }
    }

    void GAME::drawStageSelect() {
        fill(255); textSize(64);
        text("STAGE SELECT", 620, 200);

        const char* names[] = { "STAGE 1","STAGE 2","STAGE 3" };
        for (int i = 0; i < 3; i++) {
            if (i == selectedStage) { fill(255, 255, 0); text("> ", 650, 350 + i * 80); text(names[i], 690, 350 + i * 80); }
            else { fill(180); text(names[i], 680, 350 + i * 80); }
        }
        fill(200); textSize(28); text("A/D Select   ENTER Confirm   M Back Main", 620, 650);
    }

    void GAME::updatePlaying()
    {
        if (state != GameState::PLAYING) return;
        startTimer += 1.0f;
        player.update(courseManager.platforms);

        // カメラ追従
        float targetCamX = player.x - 740;
        float targetCamY = player.y - camOffsetY;

        if (player.vy < 0) {
            targetOffsetY = 780;
        }
        else {
            targetOffsetY = 740;
        }

        camOffsetY += (targetOffsetY - camOffsetY) * 0.08f;

        camX += (targetCamX - camX) * 0.1f;
        camY += (targetCamY - camY) * 0.1f;

        if (
            startTimer > 30 &&
            player.x - player.width / 2 < courseManager.goal.x + courseManager.goal.w &&
            player.x + player.width / 2 > courseManager.goal.x &&
            player.y - player.height < courseManager.goal.y + courseManager.goal.h &&
            player.y > courseManager.goal.y
            ) {
            state = GameState::FADE_OUT;
            fadeAlpha = 0.0f;
            goalTimer = 0.0f;
        }
    }

    void GAME::updateGoal()
    {
        goalTimer += 1.0f;
        fadeAlpha += 5.0f;
        if (fadeAlpha > 255) fadeAlpha = 255;
        player.vx = 0;
        player.vy = 0;
        if (fadeAlpha >= 255 && goalTimer > 60 && isTrigger(KEY_ENTER)) {
            main()->backToMenu();
        }
    }

    void GAME::updateFadeOut() {
        fadeAlpha += 4.0f;
        if (fadeAlpha >= 255) {
            fadeAlpha = 255;
            state = GameState::RESULT_WAIT;
        }
    }

    void GAME::updateResultWait() {
        if (isTrigger(KEY_ENTER)) {
            fadeAlpha = 0;
            state = GameState::STAGE_SELECT;
        }
        if (isTrigger(KEY_M)) {
            fadeAlpha = 0;
            main()->backToMenu();
        }
    }

    void GAME::drawResultUI() {
        if (state != GameState::RESULT_WAIT) return;

        fill(255);
        textSize(32);
        text("ENTER : ステージセレクト", 580, 520);
        text("M   : メインメニュー", 580, 560);
    }

    void GAME::drawWorld() {
        // 足場
        for (auto& p : courseManager.platforms) {
            p.draw(camX, camY);
        }

        // ゴール
        fill(0, 255, 0);
        rect(
            courseManager.goal.x - camX,
            courseManager.goal.y - camY,
            courseManager.goal.w,
            courseManager.goal.h
        );

        // プレイヤー
        player.draw(camX, camY);

        // GOAL文字（演出用）
        if (state == GameState::GOAL) {
            fill(255, 255, 0);
            textSize(64);
            text("GOAL!", 600, 400);
        }
    }

    void GAME::drawFade() {
        if (fadeAlpha > 0) {
            fill(0, 0, 0, (int)fadeAlpha);
            rect(0, 0, 1920, 1080);
        }
    }


    void GAME::proc()
    {
        clear(0, 0, 64);

        switch (state) {
        case GameState::STAGE_SELECT:
            updateStageSelect();
            drawStageSelect();
            break;

        case GameState::PLAYING:
            updatePlaying();
            drawWorld();
            break;

        case GameState::FADE_OUT:
            updateFadeOut();
            drawWorld();
            break;

        case GameState::RESULT_WAIT:
            updateResultWait();
            drawWorld();
            break;
        }

        drawFade();
        drawResultUI();
    }



}
