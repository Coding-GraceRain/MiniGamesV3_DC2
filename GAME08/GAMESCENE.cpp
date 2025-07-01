#include "GAMESCENE.h"
#include "../../libOne/inc/libOne.h"
namespace GAME08 {
    void GAMESCENE::create() {
        frame = 0;
        if (!assetsLoaded) {
            cutInActive = true;
            cutInFrame = 0;
            cpuTriggered = false;
            reactionFrame = -1;
            cpuReactionFrame = -1;
            cpuFrame = -1;
            resultDisplayTimer = 0;
            signalFrame = 90 + random(0, 90);
            showEx = false;
            redoRound = false;

            soraImg = loadImage("..\\MAIN\\assets\\game08\\Sora1.png");
            enemyImgs[0] = loadImage("..\\MAIN\\assets\\game08\\Usagi1.png");
            enemyImgs[1] = loadImage("..\\MAIN\\assets\\game08\\Zundamon1.png");
            enemyImgs[2] = loadImage("..\\MAIN\\assets\\game08\\Kiritan1.png");
            enemyImgs[3] = loadImage("..\\MAIN\\assets\\game08\\Zunko1.png");
            enemyImgs[4] = loadImage("..\\MAIN\\assets\\game08\\Itako1.png");

            winnerImg = loadImage("..\\MAIN\\assets\\game08\\Winner.png");

            soraNameImg = loadImage("..\\MAIN\\assets\\game08\\Sora_name.png");
            enemyNameImgs[0] = loadImage("..\\MAIN\\assets\\game08\\Usagi_name.png");
            enemyNameImgs[1] = loadImage("..\\MAIN\\assets\\game08\\Zundamon_name.png");
            enemyNameImgs[2] = loadImage("..\\MAIN\\assets\\game08\\Kiritan_name.png");
            enemyNameImgs[3] = loadImage("..\\MAIN\\assets\\game08\\Zunko_name.png");
            enemyNameImgs[4] = loadImage("..\\MAIN\\assets\\game08\\Itako_name.png");

            exImg = loadImage("..\\MAIN\\assets\\game08\\Ex.png");
            bgImg = loadImage("..\\MAIN\\assets\\game08\\StageBackground.png");

            cutinImg = loadImage("..\\MAIN\\assets\\game08\\Sora_cut.png");
            enemyCutinImgs[0] = loadImage("..\\MAIN\\assets\\game08\\Usagi_cut.png");
            enemyCutinImgs[1] = loadImage("..\\MAIN\\assets\\game08\\Zundamon_cut.png");
            enemyCutinImgs[2] = loadImage("..\\MAIN\\assets\\game08\\Kiritan_cut.png");
            enemyCutinImgs[3] = loadImage("..\\MAIN\\assets\\game08\\Zunko_cut.png");
            enemyCutinImgs[4] = loadImage("..\\MAIN\\assets\\game08\\Itako_cut.png");

            cutinX = 747;
            enemyCutinX = 1203;

            currentEnemyImg = enemyImgs[mgr.currentRound];
            currentEnemyNameImg = enemyNameImgs[mgr.currentRound];
            currentEnemyCutinImg = enemyCutinImgs[mgr.currentRound];

            assetsLoaded = true;
        }
    }

    void GAMESCENE::update() {
        frame++;
        clear(0);
        rectMode(CENTER);
        image(bgImg, width / 2, height / 2);

        float cx1 = width * 0.25f;
        float cx2 = width * 0.75f;
        float cy = height * 0.6f;

        if (cutInActive) {
            image(cutinImg, cutinX, 100);
            image(enemyCutinImgs[mgr.currentRound], enemyCutinX, height - 100);

            if (cutInFrame >= 30 && cutInFrame <= 45) {
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
        cpuFrame = signalFrame + allowedFrame + random(0, 4);

        if (frame == signalFrame) showEx = true;

        if (showEx) {
            if (mgr.mode == SCENEMANAGER::ONE_PLAYER && isPress(KEY_A)) {
                showEx = false;
            }
            else {
                image(exImg, width / 2, cy - 200, 0, 1.5f);
            }
        }

        if (mgr.mode == SCENEMANAGER::ONE_PLAYER && frame == cpuFrame) {
            cpuTriggered = true;
            cpuReactionFrame = cpuFrame - signalFrame;
        }

        if (reactionFrame < 0 && mgr.mode == SCENEMANAGER::ONE_PLAYER) {
            if (isTrigger(KEY_A)) {
                if (frame < signalFrame) {
                    foulCount++;
                    if (foulCount >= 3) {
                        mgr.change(SCENEMANAGER::RESULT);
                        return;
                    }
                    redoRound = true;
                    mgr.winner = 2;
                    resultDisplayTimer = 60;
                    return;
                }
                else {
                    reactionFrame = frame - signalFrame;
                }
            }
        }

        static int lastWinner = 0;
        if (resultDisplayTimer > 0) {
            resultDisplayTimer--;
            if (redoRound) {
                textSize(40);
                fill(255);
                text("édêÿÇËíºÇµ", width / 2 - 80, 100);
            }
            else {
                image(winnerImg, width / 2, 400, 0, 1.5);
                if (lastWinner == 1) image(soraNameImg, cx1, cy - 400);
                else if (lastWinner == 2) image(currentEnemyNameImg, cx2, cy - 400);
            }
            if (resultDisplayTimer <= 0) {
                if (redoRound) {
                    redoRound = false;
                    mgr.change(SCENEMANAGER::GAME);
                }
                else if (mgr.currentRound >= SCENEMANAGER::HISTORY_SIZE) {
                    int winCount = 0;
                    for (int i = 0; i < SCENEMANAGER::HISTORY_SIZE; ++i) {
                        if (mgr.winHistory[i] == 1) winCount++;
                    }
                    mgr.winner = (winCount == SCENEMANAGER::HISTORY_SIZE) ? 1 : 2;
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

                int cpuReact = cpuFrame - signalFrame;
                if (playerValid && !cpuTriggered) result = 1;
                else if (!playerPressed && !cpuTriggered && frame > signalFrame + allowedFrame + 120) result = 2;
                else if (playerPressed && cpuTriggered && abs(playerReact - cpuReact) <= 1) {
                    result = 3;
                    redoRound = true;
                }
                else if (playerPressed && cpuTriggered && playerReact < cpuReact) {
                    result = 1;
                }
                else {
                    result = 2;
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

        if (mgr.mode == SCENEMANAGER::ONE_PLAYER && reactionFrame >= 0) {
            textSize(48);
            fill(255);
            text("îΩâû P: " + let(reactionFrame) + "F", width - 280, height - 100);
            if (cpuReactionFrame >= 0) {
                text("îΩâû C: " + let(cpuReactionFrame) + "F", width - 280, height - 50);
            }
        }

        present();
    }

    void GAMESCENE::destroy() {
        // ì¡Ç…å„èàóùÇ»Çµ
    }

}
