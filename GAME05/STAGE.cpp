#include"../../libOne/inc/window.h"
#include"../../libOne/inc/graphic.h"
#include"../../libOne/inc/input.h"
#include"GAME.h"
#include"CONTAINER.h"
#include"FADE.h"
#include"MAP.h"
#include"LAYER.h"
#include"CHARACTER_MANAGER.h"
#include "STAGE.h"
namespace GAME05 {
    void STAGE::create() {//ステージの初期設定を行う関数
        Stage = game()->container()->data().stage;
    }
    void STAGE::init() {//ステージの初期化を行う関数
        Stage.backToTitleTime = game()->container()->data().stage.backToTitleTime;
        game()->map()->init();
        game()->layer()->init();
        game()->layer2()->init();
        game()->characterManager()->init();
        game()->fade()->inTrigger();
    }
    void STAGE::update() {//ステージの更新を行う関数
        game()->characterManager()->update();
        game()->map()->update();
        game()->layer()->update();
        game()->layer2()->update();
    }
    void STAGE::draw() {//ステージの描画を行う関数
        BackGround();
        game()->map()->draw();
        game()->characterManager()->draw();
        game()->layer2()->draw();
        game()->layer()->draw();


        if (game()->characterManager()->player()->died()) {
            Logo(Stage.gameOverImg, Stage.gameOverColor);
        }
        else if (game()->characterManager()->player()->survived()) {
            Logo(Stage.gameClearImg, Stage.gameClearColor);
        }
#ifdef _DEBUG
        fill(255);
        printSize(50);
        print(delta);
#endif
        game()->fade()->draw();
    }
    void STAGE::BackGround() {//背景の描画を行う関数
        clear();
        rectMode(CORNER);
        imageColor(Stage.backColor);
        image(Stage.backImg, 0, 0);
    }
    void STAGE::Logo(int img, const COLOR& color) {//ロゴの描画を行う関数
        imageColor(color);
        image(img, Stage.logoPx, Stage.logoPy);
        Stage.backToTitleTime -= delta;
    }
    void STAGE::nextScene() {//次のシーンに切り替える関数
        if (Stage.backToTitleTime <= 0) {
            game()->fade()->outTrigger();
        }
        if (game()->fade()->outEndFlag()) {
            game()->setCurScene(game()->title());
        }
    }
}