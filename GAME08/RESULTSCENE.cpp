#include "RESULTSCENE.h"
#include "../../libOne/inc/libOne.h"
namespace GAME08 {
    void RESULTSCENE::create() {
        // 初期化が必要ならここに
    }

    void RESULTSCENE::update() {
        clear(0);

        textSize(48);
        fill(255);
        text("リザルト", 500, 100);

        const char* resultText = "";
        switch (mgr.winner) {
        case 1: resultText = "P1の勝ち！"; break;
        case 2: resultText = "P2の勝ち！"; break;
        case 3: resultText = "引き分け！"; break;
        case 4: resultText = "フライング！"; break;
        default: resultText = "";
        }
        text(resultText, 500, 180);

        // 5回分の履歴表示
        text("直前の勝負結果：", 400, 260);
        for (int i = 0; i < SCENEMANAGER::HISTORY_SIZE; ++i) {
            const char* mark = "-";
            switch (mgr.winHistory[i]) {
            case 1: mark = "○"; break;
            case 2: mark = "×"; break;
            case 3: mark = "△"; break;
            case 4: mark = "F"; break;
            }
            text(mark, 460 + i * 60, 320);
        }

        text("ENTERキーでタイトルに戻る", 400, 500);
        if (isTrigger(KEY_ENTER)) {
            mgr.winCount = 0;
            mgr.change(SCENEMANAGER::TITLE);
        }

        present();
    }

    void RESULTSCENE::destroy() {
        // 後始末が必要ならここに
    }

}