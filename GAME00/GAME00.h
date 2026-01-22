#pragma once
#include "../MAIN/GAME_BASE.h"
#include "Player.h"
#include "Platform.h"
#include "PlatformData.h"
#include "CourseManager.h"
#include "Courses.h"

namespace GAME00 {

    enum class GameState {
        STAGE_SELECT,
        PLAYING,
        GOAL,
        FADE_OUT,
        RESULT_WAIT
    };



    class GAME : public GAME_BASE {
    public:
        GAME(class MAIN* main) : GAME_BASE(main) {}
        ~GAME() {}

        int create();
        void proc();
        void destroy();

    private:
        Player player;
        float camX = 0, camY = 0;
        float camOffsetY = 920, targetOffsetY = 920;
        bool isGoal = false;
        float goalTimer = 0;
        float fadeAlpha = 0;
        float startTimer = 0;

        CourseManager courseManager;
        int selectedStage = 0;
        GameState state = GameState::STAGE_SELECT;

        void updateStageSelect();
        void drawStageSelect();
        void updatePlaying();
        void updateGoal();
        void drawResultUI();
        void updateResultWait();
        void updateFadeOut();
        void drawWorld();
        void drawFade();
    };
}
