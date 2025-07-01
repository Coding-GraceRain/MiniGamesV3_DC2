#include "RESULTSCENE.h"
#include "../../libOne/inc/libOne.h"
namespace GAME08 {
    void RESULTSCENE::create() {
        if (!assetsLoaded) {
            bgImg = loadImage("..\\MAIN\\assets\\game08\\TitleBackground.png");
            assetsLoaded = true;
        }
    }

    void RESULTSCENE::update() {
        clear(0);
        float px = width / 2;
        float py = height / 2;
        rectMode(CENTER);
        image(bgImg, px, py);
        fill(255, 0, 100);
        rect(px, py - 200, px + 50, py);
        fill(255);
        rect(px, py - 200, px, py - 50);

        textSize(48);
        fill(0);
        text("���U���g", px - 75, 250);

        const char* resultText = "";
        switch (mgr.winner) {
        case 1: resultText = "P1�̏����I"; break;
        case 2: resultText = "NPC�̏����I"; break;
        case 3: resultText = "���������I"; break;
        case 4: resultText = "�t���C���O�I"; break;
        default: resultText = "";
        }
        text(resultText, px - 90, 300);

        // 5�񕪂̗���\��
        text("���O�̏�������", px - 150, 350);
        for (int i = 0; i < SCENEMANAGER::HISTORY_SIZE; ++i) {
            const char* mark = "-";
            switch (mgr.winHistory[i]) {
            case 1: mark = "��"; break;
            case 2: mark = "�~"; break;
            case 3: mark = "��"; break;
            case 4: mark = "F"; break;
            }
            text(mark, px - 130 + i * 60, 400);
        }

        text("ENTER�L�[�Ń^�C�g���ɖ߂�", px - 280, 500);
        if (isTrigger(KEY_ENTER)) {
            mgr.winCount = 0;
            mgr.change(SCENEMANAGER::TITLE);
        }

        present();
    }

    void RESULTSCENE::destroy() {
        // ��n�����K�v�Ȃ炱����
    }

}