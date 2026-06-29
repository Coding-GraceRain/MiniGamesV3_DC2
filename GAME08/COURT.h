#pragma once
#include "ACTOR.h"
namespace GAME08 {
    class COURT :
        public ACTOR
    {
    public:
        COURT(class GAME* game);
		~COURT();
		void init();
		void update();
		void draw();
    };
}

