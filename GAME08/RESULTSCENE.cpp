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
        text("リザルト", px - 75, 250);

        const char* resultText = "";
        switch (mgr.winner) {
        case 1: resultText = "P1の勝ち！"; break;
        case 2: resultText = "NPCの勝ち！"; break;
        case 3: resultText = "引き分け！"; break;
        //case 4: resultText = "フライング！"; break;
        default: resultText = "";
        }
        text(resultText, px - 90, 300);

        // 5回分の履歴表示
        text("直前の勝負結果", px - 150, 350);
        for (int i = 0; i < SCENEMANAGER::HISTORY_SIZE; ++i) {
            const char* mark = "-";
            switch (mgr.winHistory[i]) {
            case 1: mark = "○"; break;
            case 2: mark = "×"; break;
            case 3: mark = "△"; break;
            //case 4: mark = "F"; break;
            }
            text(mark, px - 130 + i * 60, 400);
        }

        text("ENTERキーでタイトルに戻る", px - 280, 500);
        if (isTrigger(KEY_ENTER)) {
            mgr.currentRound = 0;
            mgr.winCount = 0;
            mgr.change(SCENEMANAGER::TITLE);
        }

        //present();
    }

    void RESULTSCENE::destroy() {
        // 後始末が必要ならここに
    }

}