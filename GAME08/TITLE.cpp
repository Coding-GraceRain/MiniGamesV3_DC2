#include "../../libOne/inc/libOne.h"
#include "../../libOne/inc/input.h"
#include "TITLE.h"
#include "../MAIN/MAIN.h"
#include "GAME08.h"

namespace GAME08
{
    int TITLE::create()
    {
        return 0;
    }

    void TITLE::destroy()
    {

    }

    void TITLE::proc()
    {
        clear(0);

        // タイトル
        fill(255, 255, 0);
        textSize(80);
        textMode(BCENTER);
        text("PONG", 640, 180);

        // 操作説明
        fill(255);
        textSize(35);
        text("Player2 : J 　 L", 640, 320);
        text("Player1 : A    D", 640, 380);

        // 開始案内
        fill(0, 255, 0);
        textSize(40);
        text("ENTER押してスタート", 640, 520);
        if (isTrigger(KEY_ENTER))
        {
            // GAME08へ切り替える
          main()->setNextGameId(GAME_FACTORY::GAME08_ID);
        }
    }
}