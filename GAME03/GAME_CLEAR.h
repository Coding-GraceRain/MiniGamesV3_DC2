#pragma once
#include "SCENE.h"
namespace GAME03
{
    class GAME_CLEAR :
        public SCENE
    {
    public:
        struct DATA {
            COLOR textColor;
            float textSize = 0;
            VECTOR2 pos;
            char str[16];
            char instructions[30];
        };
    private:
        DATA GameClear;
    public:
        GAME_CLEAR(class GAME* game);
        ~GAME_CLEAR();
        void init();
        void create();
        void draw();
        void nextScene();
    };
}
