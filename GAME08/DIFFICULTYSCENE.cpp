#include "DIFFICULTYSCENE.h"
#include "../../libOne/inc/libOne.h"
#include "../MAIN/MAIN.h"
namespace GAME08 {
    void DIFFICULTYSCENE::create() {
        // 初期化処理があればここに
    }

    void DIFFICULTYSCENE::update() {
        clear(0);
        fill(255);
        textSize(36);

        text("【難易度選択】", 100, 100);
        text("Zキー：易（反応猶予長め）", 100, 180);
        text("Xキー：中（標準）", 100, 240);
        text("Cキー：難（反応猶予短い）", 100, 300);

        text("キーを押してゲーム開始", 100, 420);

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
        // 後始末があればここに
    }
}