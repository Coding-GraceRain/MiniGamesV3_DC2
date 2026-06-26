#pragma once
#include "GAME_OBJECT.h"
namespace GAME03
{
    class CHARACTER :
        public GAME_OBJECT
    {
    public:
        struct DATA {
            int img = 0;
            int gimmickImg = 0;
            char charaId = 0;
            int groupId = 0;
            int hp = 0;
            float x = 0;
            float y = 0;
            float vx = 0;
            float vy = 0;
            float speed = 0;

            float offsetLeft = 0;
            float offsetTop = 0;
            float offsetRight = 0;
            float offsetBottom = 0;
        };
    protected:
        DATA Chara;
    public:
        CHARACTER(class GAME* game);
        virtual void create();
        virtual void init();
        virtual void appear(float x, float y, float vx, float vy);
        virtual void update();
        virtual void draw();
        virtual void damage();
        int hp() { return Chara.hp; }
        int groupId() { return Chara.groupId; }
        char charaId() { return Chara.charaId; }
        float wLeft() { return Chara.x + Chara.offsetLeft; }
        float wTop() { return Chara.y + Chara.offsetTop; }
        float wRight() { return Chara.x + Chara.offsetRight; }
        float wBottom() { return Chara.y + Chara.offsetBottom; }
    };
}
