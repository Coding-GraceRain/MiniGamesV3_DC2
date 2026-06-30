#include"../../libOne/inc/graphic.h"
#include"../../libOne/inc/input.h"
#include "../../libOne/inc/libOne.h"
#include"GAME.h"
#include"CONTAINER.h"
#include"STAGE.h"
#include"FADE.h"
#include "TITLE.h"
namespace GAME05 {
    void TITLE::init() {//シーンの初期化を行う関数
        game()->fade()->inTrigger();
    }
    void TITLE::draw() {//シーンの描画を行う関数
        clear();
        rectMode(CORNER);
        imageColor(240);
        image(game()->container()->data().title.backImg, 0, 0);
        float size;

        size = 50;
        textSize(size);
        fill(255);
        text("A......Left  ", (width - size / 2 * 13) / 2, 290);
        text("D......Right  ", (width - size / 2 * 13) / 2, 360);
        text("J......Jump  ", (width - size / 2 * 13) / 2, 430);
        text("L......attack  ", (width - size / 2 * 13) / 2, 500);
        fill(255, 0, 255);
        text("SPACEでスタート", (width - size / 2 * 15) / 2, 1000);

        game()->fade()->draw();
    }
    void TITLE::nextScene() {//次のシーンに切り替える関数
        if (isTrigger(KEY_SPACE)) {

            game()->fade()->outTrigger();
        }

        if (game()->fade()->outEndFlag()) {
            game()->setCurScene(game()->stage());
        }
    }
}