#include "GAMESCENE.h"
#include "../../libOne/inc/libOne.h"
namespace GAME08 {
    void GAMESCENE::create() {
        frame = 0;
        cutInActive = true;
        cutInFrame = 0;
        cpuTriggered = false;
        reactionFrame = -1;
        resultDisplayTimer = 0;
        signalFrame = 90 + random(0, 90); // ランダム待機
        showEx = false;
        redoRound = false;

        //キャラ画像
        soraImg = loadImage("..\\MAIN\\assets\\game08\\Sora1.png");
        enemyImgs[0] = loadImage("..\\MAIN\\assets\\game08\\Usagi1.png");
        enemyImgs[1] = loadImage("..\\MAIN\\assets\\game08\\Zundamon1.png");
        enemyImgs[2] = loadImage("..\\MAIN\\assets\\game08\\Kiritan1.png");
        enemyImgs[3] = loadImage("..\\MAIN\\assets\\game08\\Zunko1.png");
        enemyImgs[4] = loadImage("..\\MAIN\\assets\\game08\\Itako1.png");
        //勝者
        winnerImg = loadImage("..\\MAIN\\assets\\game08\\Winner.png");
        //キャラの名前
        soraNameImg = loadImage("..\\MAIN\\assets\\game08\\Sora_name.png");
        enemyNameImgs[0] = loadImage("..\\MAIN\\assets\\game08\\Usagi_name.png");
        enemyNameImgs[1] = loadImage("..\\MAIN\\assets\\game08\\Zundamon_name.png");
        enemyNameImgs[2] = loadImage("..\\MAIN\\assets\\game08\\Kiritan_name.png");
        enemyNameImgs[3] = loadImage("..\\MAIN\\assets\\game08\\Zunko_name.png");
        enemyNameImgs[4] = loadImage("..\\MAIN\\assets\\game08\\Itako_name.png");
        //演出＆背景
        exImg = loadImage("..\\MAIN\\assets\\game08\\Ex.png");
        bgImg = loadImage("..\\MAIN\\assets\\game08\\StageBackground.png");
        //カットイン素材
        cutinImg = loadImage("..\\MAIN\\assets\\game08\\Sora_cut.png");
        enemyCutinImgs[0] = loadImage("..\\MAIN\\assets\\game08\\Usagi_cut.png");
        enemyCutinImgs[1] = loadImage("..\\MAIN\\assets\\game08\\Zundamon_cut.png");
        enemyCutinImgs[2] = loadImage("..\\MAIN\\assets\\game08\\Kiritan_cut.png");
        enemyCutinImgs[3] = loadImage("..\\MAIN\\assets\\game08\\Zunko_cut.png");
        enemyCutinImgs[4] = loadImage("..\\MAIN\\assets\\game08\\Itako_cut.png");

        cutinX = 777;
        enemyCutinX = 1203;

        currentEnemyImg = enemyImgs[mgr.currentRound];
        currentEnemyNameImg = enemyNameImgs[mgr.currentRound];
        currentEnemyCutinImg = enemyCutinImgs[mgr.currentRound];
    }

    void GAMESCENE::update() {
        clear(0);
        rectMode(CENTER);
        image(bgImg, width / 2, height / 2);

        //プレイヤーと敵の位置
        float cx1 = width * 0.25f;
        float cx2 = width * 0.75f;
        float cy = height * 0.6f;

        if (cutInActive) {
            image(cutinImg, cutinX, 100);
            image(enemyCutinImgs[mgr.currentRound], enemyCutinX, height - 100);
            
            if (cutInFrame >= 30 && cutInFrame < 45) {
                float movePerFrame = 425.0f / 15.0f;
                cutinX += movePerFrame;
                enemyCutinX -= movePerFrame;
            }

            cutInFrame++;
            if (cutInFrame >= CUT_IN_DURATION) {
                cutInActive = false;
                frame = 0;
            }
            present();
            return;
        }

        frame++;

        image(soraImg, cx1, cy);
        image(currentEnemyImg, cx2, cy);

        if (foulCount > 0) {
            for (int i = 0; i < foulCount && i < 2; ++i) {
                float fx = cx1;
                float fy = cy - 200 - i * 40;
                stroke(255, 0, 0);
                strokeWeight(5);
                line(fx - 20, fy - 20, fx + 20, fy + 20);
                line(fx - 20, fy + 20, fx + 20, fy - 20);
            }
        }

        int allowedFrame = mgr.difficultyFrame[mgr.currentDifficulty][mgr.currentRound];
        int cpuFrame = signalFrame + allowedFrame + random( 0,4); //CPUの反応タイミング

        if (frame == signalFrame) {
            showEx = true;
        }

        if (showEx) {
            image(exImg, width / 2, cy - 200,0,1.5f);
        }

        if (mgr.mode == SCENEMANAGER::ONE_PLAYER && frame == cpuFrame) {
            cpuTriggered = true;
        }

        if (reactionFrame < 0) {
            if (mgr.mode == SCENEMANAGER::ONE_PLAYER) {
                if (isTrigger(KEY_A)) {
                    if (frame < signalFrame) {
                        foulCount++;
                        if (foulCount >= 3) {
                            mgr.change(SCENEMANAGER::RESULT);
                            return;
                        }
                        redoRound = true;
                        mgr.winner = 2; // 表示用に CPU勝ち扱い
                        resultDisplayTimer = 60;
                        return;
                    }
                    else {
                        reactionFrame = frame - signalFrame;
                    }
                }
            }
        }

        static int lastWinner = 0;

        if (resultDisplayTimer > 0) {
            resultDisplayTimer--;
            if (redoRound) {
                textSize(40);
                fill(255);
                text("仕切り直し", width / 2 - 80, 100);
            }
            else {
                image(winnerImg, width / 2, 400);

                if (lastWinner == 1) {
                    image(soraNameImg, cx1, cy - 500);
                }
                else if (lastWinner == 2) {
                    image(currentEnemyNameImg, cx2, cy - 500);
                }
            }

            if (resultDisplayTimer <= 0) {
                if (redoRound) {
                    redoRound = false;
                    mgr.change(SCENEMANAGER::GAME);
                }
                else if (mgr.currentRound >= SCENEMANAGER::HISTORY_SIZE) {
                    mgr.change(SCENEMANAGER::RESULT);
                }
                else {
                    mgr.change(SCENEMANAGER::GAME);
                }
            }
            present();
            return;
        }

        if (frame > signalFrame + allowedFrame) {
            int result = 0;

            if (mgr.mode == SCENEMANAGER::ONE_PLAYER) {
                bool playerPressed = reactionFrame >= 0;
                int playerReact = reactionFrame;
                bool playerValid = playerPressed && playerReact <= allowedFrame;

                if (playerValid && !cpuTriggered) result = 1;
                else if (!playerPressed && !cpuTriggered && frame > signalFrame + allowedFrame + 120) result = 2; // 時間切れでCPU勝ち
                else if (playerPressed && cpuTriggered && abs(playerReact - (cpuFrame - signalFrame)) <= 1) {
                    result = 3;
                    redoRound = true;
                }
                else result = 2;
            }
            else if (mgr.mode == SCENEMANAGER::TWO_PLAYER) {
                if (p1ReactionFrame < 0 && isTrigger(KEY_A)) {
                    p1ReactionFrame = frame - signalFrame;
                }
                if (p2ReactionFrame < 0 && isTrigger(KEY_L)) {
                    p2ReactionFrame = frame - signalFrame;
                }

                if ((p1ReactionFrame >= 0 && p2ReactionFrame < 0 && frame > signalFrame + p1ReactionFrame + 30)) {
                    result = 1;
                }
                else if ((p2ReactionFrame >= 0 && p1ReactionFrame < 0 && frame > signalFrame + p2ReactionFrame + 30)) {
                    result = 2;
                }
                else if (p1ReactionFrame >= 0 && p2ReactionFrame >= 0) {
                    if (abs(p1ReactionFrame - p2ReactionFrame) <= 1) {
                        result = 3;
                        redoRound = true;
                    }
                    else if (p1ReactionFrame < p2ReactionFrame) {
                        result = 1;
                    }
                    else {
                        result = 2;
                    }
                }
                else if (frame > signalFrame + 120) {
                    result = 2; // 両者無反応でタイムアップ → 2P勝ち
                }
            }

            if (result != 3) {
                mgr.winHistory[mgr.currentRound] = result;
                mgr.currentRound++;
            }
            mgr.winner = result;
            lastWinner = result;
            resultDisplayTimer = 60;
        }


        //右下にリアクションフレームを表示
        if (reactionFrame >= 0) {
            fill(255);
            textSize(36);
            text("", width - 500, height - 50);
        }
        present();
    }

    void GAMESCENE::destroy() {
        // 特に後処理なし
    }
}
