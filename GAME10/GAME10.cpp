#include "../../libOne/inc/libOne.h"
#include "../MAIN/MAIN.h"
#include "GAME10.h"
#include <cstdlib>
#include <ctime>

namespace GAME10 {

    const int CARD_COUNT = 13;
    int cardImgs[CARD_COUNT];
    int soundBGM;
    int a, b;
    int streak = 0;
    int maxStreak = 0;
    int score = 0;
    int maxScore = 0;
    int state = -1;  // -1:ルール説明, 0:待機中, 1:結果表示
    char resultStr[64] = "";

    int GAME::create() {
        for (int i = 0; i < CARD_COUNT; i++) {
            char filename[64];
            sprintf_s(filename, sizeof(filename), "../MAIN/assets/game10/%d.png", i + 1);
            cardImgs[i] = loadImage(filename);
            soundBGM = loadSound("../MAIN/assets/game10/14.wav");
                                                                             //playLoopSound ...BGM
                                                                             //playSound...SE
        }                                                                    //stopSound...BGMを止める　
                                                                             //volume
                                                                             //pan 

        srand((unsigned)time(NULL));
        a = rand() % CARD_COUNT + 1;
        return 0;
    }

    void GAME::destroy() {}

    void GAME::proc() {
        clear(0, 0, 64);

        // ルール説明画面
        if (state == -1) {
            textSize(50);
            fill(255, 255, 0);
            text("【ルール説明】", 700, 100);

            textSize(40);
            fill(255);
            text("表示されたカードより次のカードが", 100, 250);
            text("High（↑）か Low（↓）かを予想してください。", 100, 310);
            text("当たると連続正解・スコアが加算されます。", 100, 370);
            text("3回目以降の連続正解はスコアが倍になります！", 100, 430);
            text("外れるとスコアは0になります。", 100, 490);

            fill(255, 255, 255);
            text("スペースキーでゲームスタート", 100, 600);
            text("Enterキーでメニューに戻る", 100, 700);

            if (isTrigger(KEY_SPACE)) {
                state = 0;
                playLoopSound(soundBGM);
            }
            if (isTrigger(KEY_ENTER)) main()->backToMenu();
            return;
        }

        // スコア・連続表示
        textSize(50);
        fill(255, 255, 255);
        char streakStr[64];
        sprintf_s(streakStr, sizeof(streakStr), "連続正解: %d 回", streak);
        text(streakStr, 50, 50);

        char maxStr[64];
        sprintf_s(maxStr, sizeof(maxStr), "最大連続: %d 回", maxStreak);
        text(maxStr, 50, 110);

        char scoreStr[64];
        sprintf_s(scoreStr, sizeof(scoreStr), "スコア: %d 点", score);
        text(scoreStr, 50, 170);

        char maxScoreStr[64];
        sprintf_s(maxScoreStr, sizeof(maxScoreStr), "最大スコア: %d 点", maxScore);
        text(maxScoreStr, 50, 230);



        float cardY = 40.0f;
        int cardSpacing = 200;
        int baseX = 1920 / 2 - 100;
        float cardX1 = baseX - cardSpacing;
        float cardX2 = baseX + cardSpacing;

        image(cardImgs[a - 1], cardX1, cardY);

        textSize(40);
        fill(255);

        if (state == 0) {
            text("↑キー：High", 50, 850);
            text("↓キー：Low", 50, 900);

            if (isTrigger(KEY_UP) || isTrigger(KEY_DOWN)) {
                bool isHigh = isTrigger(KEY_UP);
                b = rand() % CARD_COUNT + 1;
                bool correct = (isHigh && b > a) || (!isHigh && b < a);

                if (correct) {
                    streak++;
                    if (streak > maxStreak) maxStreak = streak;
                    int gain = (streak >= 3) ? 20 : 10;
                    score += gain;
                    if (score > maxScore) maxScore = score;
                    sprintf_s(resultStr, sizeof(resultStr), "正解！+%d点 連続 %d 回", gain, streak);
                }
                else if (b == a) {
                    sprintf_s(resultStr, sizeof(resultStr), "引き分け！カウントそのまま(%d回)", streak);
                }
                else {
                    streak = 0;
                    score = 0;
                    sprintf_s(resultStr, sizeof(resultStr), "不正解!スコアリセット");
                }
                state = 1;
            }
        }
        else if (state == 1) {
            textSize(38);
            image(cardImgs[b - 1], cardX2, cardY);
            text(resultStr, 50, 850);
            text("スペースキーで次のゲームへ", 50, 900);

            if (isTrigger(KEY_SPACE)) {

                a = b;
                state = 0;
            }
        }

        text("Enterキーでメニューに戻る", 50, 1000);
        if (isTrigger(KEY_ENTER)) {
            stopSound(soundBGM);
            main()->backToMenu();
        }
    }

}