#include "TITLESCENE.h"
#include "../../libOne/inc/libOne.h"
namespace GAME08 {
    void TITLESCENE::create() {
        if (!assetsLoaded) {
            bgImg = loadImage("..\\MAIN\\assets\\game08\\Titlebackground.png");
            assetsLoaded = true;
        }
        select = 0;
        difficultySelect = 0;
        selectingDifficulty = false;
    }

    void TITLESCENE::update() {
        clear(0);

        rectMode(CENTER);
        image(bgImg, width / 2, height / 2);

        // �^�C�g���\���i�㕔�j
        textSize(200);
        fill(255);
        text("��", width / 2 - 400, 280);

        textSize(150);
        text("��", width / 2 - 200, 260);

        textSize(100);
        text("��", width / 2 - 70, 230);

        textSize(150);
        text("��", width / 2, 260);

        textSize(200);
        fill(255, 0, 0);
        text("�a", width / 2 + 130, 280);

        textSize(120);
        fill(255);
        text("��", width / 2 + 300, 250);

        fill(0, 255, 0);
        rect(width / 2, height / 2 - 60, width / 2 + 30, height / 3 + 20);
        fill(255);
        rect(width / 2, height / 2 - 60, width / 2 - 10, height / 3 - 20);

        fill(0);
        textSize(80);
        text("�w�I�x�}�[�N���A", width / 2 - 500, 420);
        text("�����ꂽ��A", width / 2 - 100, 520);
        text("�������� A ���������I", width / 2 - 460, 620);

        // �v���C���[�h�I��
        textSize(48);
        fill(255);

        float baseY = height * 0.75f;
        float optionX1 = width / 2 - 150;
        float optionX2 = width / 2 + 60;

        fill(227, 162, 36);
        rect(width / 2 - 20, baseY - 23, width / 4 - 80, 110);
        fill(255);
        rect(width / 2 - 20, baseY - 23, width / 4 - 100, 90);

        fill(0, 0, 255);
        text("1", optionX1, baseY);
        fill(0);
        text("�l", optionX1 + 48, baseY);
        //fill(255, 0, 0);
        //text("2", optionX2, baseY);
        //fill(0);
        //text("�l", optionX2 + 48, baseY);

        // �I�𒆂̍��ɎO�p�`
        //float markerX = (select == 0) ? optionX1 - 40 : optionX2 - 40;
        float markerX = optionX1 - 40;
        float markerY = baseY;
        textSize(48);
        fill(0);
        text("��", markerX, markerY);

        fill(227, 162, 36);
        rect(width / 2 - 20, baseY + 150, width / 4+20, 110);
        fill(255);
        rect(width / 2 - 20, baseY + 150, width / 4, 90);
        fill(0);
        text("A�Ō���@�����őI��", optionX1-100, baseY + 170);

        if (selectingDifficulty) {
            const char* difficultyLabels[] = { "��", "��", "��" };
            float difficultyBaseX = optionX1;
            float difficultyY = baseY;

            fill(227, 162, 36);
            rect(width / 2 - 20, baseY - 23, width / 4 - 80, 110);
            fill(255);
            rect(width / 2 - 20, baseY - 23, width / 4 - 100, 90);

            //��Փx�\��
            for (int i = 0; i < 3; ++i) {
                if (i == 0) {
                    fill(0, 0, 255);
                }
                else if (i == 1) {
                    fill(255, 0, 255);
                }
                else if(i == 2) {
                    fill(255, 0, 0);
                }
                text(difficultyLabels[i], difficultyBaseX + i * 100, difficultyY);
            }

            // �O�p�`�J�[�\���i������j
            float triX = difficultyBaseX + difficultySelect * 100;
            float triY = difficultyY + 50;
            fill(0, 255, 0);
            text("��", triX, triY);

            //���͏���
            if (isTrigger(KEY_LEFT)) {
                if (difficultySelect > 0) difficultySelect--;
            }
            else if (isTrigger(KEY_RIGHT)) {
                if (difficultySelect < 2) difficultySelect++;
            }
            else if (isTrigger(KEY_A)) {
                mgr.mode = (select == 0) ? SCENEMANAGER::ONE_PLAYER : SCENEMANAGER::TWO_PLAYER;
                mgr.currentDifficulty = (SCENEMANAGER::DIFFICULTY_LEVEL)(difficultySelect);
                mgr.change(SCENEMANAGER::GAME);
            }
        }
        else {
            if (isTrigger(KEY_A)) {
                mgr.mode = SCENEMANAGER::ONE_PLAYER;
                selectingDifficulty = true;
            }
            /*if (isTrigger(KEY_LEFT)) {
                select = 0;
            }
            else if (isTrigger(KEY_RIGHT)) {
                select = 1;
            }
            else if (isTrigger(KEY_A)) {
                selectingDifficulty = true;
            }*/
        }
        


        present();
    }

    void TITLESCENE::destroy() {
        // �K�v������΂����Ɍ�n��
    }

}
