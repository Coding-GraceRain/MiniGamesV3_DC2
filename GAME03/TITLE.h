#pragma once
#include "../../libOne/inc/libOne.h"
#include "SCENE.h"
namespace GAME03
{
    class TITLE :
        public SCENE
    {
    public:
        struct DATA {
            COLOR backColor;
            COLOR textColor;
            float textSize = 0;
            VECTOR2 pos;
            char str[16];
            char instructions[30];
        };
    private:
        DATA Title;
    public:
        TITLE(class GAME* game);
        ~TITLE();
        void init();
        void create();
        void draw();
        void nextScene();
    };
}
