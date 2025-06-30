#pragma once
#include"SCENEBASE.h"
#include "../../libOne/inc/libOne.h"
namespace GAME08 {
    class SCENEMANAGER {
        SCENEBASE* current = nullptr;
    public:
        enum SCENEID { TITLE, DIFFICULTY, GAME, RESULT };
        enum DIFFICULTY_LEVEL { EASY,  NORMAL,  HARD };
        enum PLAY_MODE{ ONE_PLAYER, TWO_PLAYER };

        DIFFICULTY_LEVEL currentDifficulty = NORMAL;
        PLAY_MODE mode = TWO_PLAYER;

        static const int HISTORY_SIZE = 5;

        // 難易度別フレーム設定：difficultyFrame[難易度][ラウンド]
        int difficultyFrame[3][HISTORY_SIZE] = {
            { 90, 75, 60, 45, 35 }, // EASY
            { 60, 50, 40, 30, 25 },  // NORMAL
            { 30, 28, 23, 20, 16 }     // HARD
        };

        int winCount = 0;
        int winner = 0;
        int winHistory[HISTORY_SIZE] = { 0 };

        int currentRound = 0;
        COLOR characterColors[HISTORY_SIZE] = {
            COLOR(255, 255, 255),  // 白
            COLOR(255, 0, 0),      // 赤
            COLOR(0, 255, 0),      // 緑
            COLOR(0, 0, 255),      // 青
            COLOR(255, 255, 0)     // 黄
        };

        void change(SCENEID id);
        void update();
        void shutdown();
    };

}
