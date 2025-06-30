#include "RESULTSCENE.h"
#include "../../libOne/inc/libOne.h"
namespace GAME08 {
    void RESULTSCENE::create() {
        // ���������K�v�Ȃ炱����
    }

    void RESULTSCENE::update() {
        clear(0);

        textSize(48);
        fill(255);
        text("���U���g", 500, 100);

        const char* resultText = "";
        switch (mgr.winner) {
        case 1: resultText = "P1�̏����I"; break;
        case 2: resultText = "P2�̏����I"; break;
        case 3: resultText = "���������I"; break;
        case 4: resultText = "�t���C���O�I"; break;
        default: resultText = "";
        }
        text(resultText, 500, 180);

        // 5�񕪂̗���\��
        text("���O�̏������ʁF", 400, 260);
        for (int i = 0; i < SCENEMANAGER::HISTORY_SIZE; ++i) {
            const char* mark = "-";
            switch (mgr.winHistory[i]) {
            case 1: mark = "��"; break;
            case 2: mark = "�~"; break;
            case 3: mark = "��"; break;
            case 4: mark = "F"; break;
            }
            text(mark, 460 + i * 60, 320);
        }

        text("ENTER�L�[�Ń^�C�g���ɖ߂�", 400, 500);
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