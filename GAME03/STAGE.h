#pragma once
#include "SCENE.h"
namespace GAME03
{
    class STAGE :
        public SCENE
    {
    public:
        struct DATA {
            float respawnPlayerTime = 0;
            float nextSceneTime = 0;
            const char* stageNum = 0;
            const char* stage01 = 0;
            const char* stage02 = 0;
            const char* stage03 = 0;
            const char* stage04 = 0;
            const char* stage05 = 0;
            float size = 0;
            float tx = 0, ty = 0;
        };
    private:
        DATA Stage;
        enum class STAGE_NUMBER {
            STAGE01,
            STAGE02,
            STAGE03,
            STAGE04,
            STAGE05,
        };
        STAGE_NUMBER StageNum = STAGE_NUMBER::STAGE01;
    public:

        STAGE(class GAME* game);
        ~STAGE();
        void create();
        void init();
        void update();
        void respawn();
        void tutorial();
        void draw();
        void Logo();
        void nextStage();
        void nextScene();
    };
}
