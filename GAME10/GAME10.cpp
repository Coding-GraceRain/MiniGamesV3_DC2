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
    int state = -1;  // -1:���[������, 0:�ҋ@��, 1:���ʕ\��
    char resultStr[64] = "";

    int GAME::create() {
        for (int i = 0; i < CARD_COUNT; i++) {
            char filename[64];
            sprintf_s(filename, sizeof(filename), "../MAIN/assets/game10/%d.png", i + 1);
            cardImgs[i] = loadImage(filename);
            soundBGM = loadSound("../MAIN/assets/game10/14.wav");
                                                                             //playLoopSound ...BGM
                                                                             //playSound...SE
        }                                                                    //stopSound...BGM���~�߂�@
                                                                             //volume
                                                                             //pan 

        srand((unsigned)time(NULL));
        a = rand() % CARD_COUNT + 1;
        return 0;
    }

    void GAME::destroy() {}

    void GAME::proc() {
        clear(0, 0, 64);

        // ���[���������
        if (state == -1) {
            textSize(50);
            fill(255, 255, 0);
            text("�y���[�������z", 700, 100);

            textSize(40);
            fill(255);
            text("�\�����ꂽ�J�[�h��莟�̃J�[�h��", 100, 250);
            text("High�i���j�� Low�i���j����\�z���Ă��������B", 100, 310);
            text("������ƘA�������E�X�R�A�����Z����܂��B", 100, 370);
            text("3��ڈȍ~�̘A�������̓X�R�A���{�ɂȂ�܂��I", 100, 430);
            text("�O���ƃX�R�A��0�ɂȂ�܂��B", 100, 490);

            fill(255, 255, 255);
            text("�X�y�[�X�L�[�ŃQ�[���X�^�[�g", 100, 600);
            text("Enter�L�[�Ń��j���[�ɖ߂�", 100, 700);

            if (isTrigger(KEY_SPACE)) {
                state = 0;
                playLoopSound(soundBGM);
            }
            if (isTrigger(KEY_ENTER)) main()->backToMenu();
            return;
        }

        // �X�R�A�E�A���\��
        textSize(50);
        fill(255, 255, 255);
        char streakStr[64];
        sprintf_s(streakStr, sizeof(streakStr), "�A������: %d ��", streak);
        text(streakStr, 50, 50);

        char maxStr[64];
        sprintf_s(maxStr, sizeof(maxStr), "�ő�A��: %d ��", maxStreak);
        text(maxStr, 50, 110);

        char scoreStr[64];
        sprintf_s(scoreStr, sizeof(scoreStr), "�X�R�A: %d �_", score);
        text(scoreStr, 50, 170);

        char maxScoreStr[64];
        sprintf_s(maxScoreStr, sizeof(maxScoreStr), "�ő�X�R�A: %d �_", maxScore);
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
            text("���L�[�FHigh", 50, 850);
            text("���L�[�FLow", 50, 900);

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
                    sprintf_s(resultStr, sizeof(resultStr), "�����I+%d�_ �A�� %d ��", gain, streak);
                }
                else if (b == a) {
                    sprintf_s(resultStr, sizeof(resultStr), "���������I�J�E���g���̂܂�(%d��)", streak);
                }
                else {
                    streak = 0;
                    score = 0;
                    sprintf_s(resultStr, sizeof(resultStr), "�s����!�X�R�A���Z�b�g");
                }
                state = 1;
            }
        }
        else if (state == 1) {
            textSize(38);
            image(cardImgs[b - 1], cardX2, cardY);
            text(resultStr, 50, 850);
            text("�X�y�[�X�L�[�Ŏ��̃Q�[����", 50, 900);

            if (isTrigger(KEY_SPACE)) {

                a = b;
                state = 0;
            }
        }

        text("Enter�L�[�Ń��j���[�ɖ߂�", 50, 1000);
        if (isTrigger(KEY_ENTER)) {
            stopSound(soundBGM);
            main()->backToMenu();
        }
    }

}