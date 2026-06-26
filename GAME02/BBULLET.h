#pragma once
#include"BULLET_BASE.h"
#include "PLAYER.H"

namespace GAME02 {
	class BBULLET 
		:public BULLET_BASE
	{		
	public:
		float Deg;
		void init();
		void create();
		void update();
		void draw();
		void set(float x, float y, float vx, float vy);
		bool hit(PLAYER& player);

		float left();
		float right();
		float top();
		float bottom();
	};
}

