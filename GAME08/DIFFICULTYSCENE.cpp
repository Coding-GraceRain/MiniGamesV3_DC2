#include "DIFFICULTYSCENE.h"
#include "../../libOne/inc/libOne.h"
#include "../MAIN/MAIN.h"
namespace GAME08 {
    void DIFFICULTYSCENE::create() {
        // ����������������΂�����
    }

    void DIFFICULTYSCENE::update() {
        clear(0);
        fill(255);
        textSize(36);

        text("�y��Փx�I���z", 100, 100);
        text("Z�L�[�F�Ձi�����P�\���߁j", 100, 180);
        text("X�L�[�F���i�W���j", 100, 240);
        text("C�L�[�F��i�����P�\�Z���j", 100, 300);

        text("�L�[�������ăQ�[���J�n", 100, 420);

        if (isTrigger(KEY_Z)) {
            mgr.currentDifficulty = SCENEMANAGER::EASY;
            mgr.change(SCENEMANAGER::GAME);
        }
        else if (isTrigger(KEY_X)) {
            mgr.currentDifficulty = SCENEMANAGER::NORMAL;
            mgr.change(SCENEMANAGER::GAME);
        }
        else if (isTrigger(KEY_C)) {
            mgr.currentDifficulty = SCENEMANAGER::HARD;
            mgr.change(SCENEMANAGER::GAME);
        }

        present();
    }

    void DIFFICULTYSCENE::destroy() {
        // ��n��������΂�����
    }
}