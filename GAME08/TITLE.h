#pragma once
#include "../MAIN/GAME_BASE.h"

namespace GAME08
{
    class TITLE : public GAME_BASE
    {
    public:
        TITLE(class MAIN* main) : GAME_BASE(main) {}
        ~TITLE() {}

        int create();
        void proc();
        void destroy();
    };
}