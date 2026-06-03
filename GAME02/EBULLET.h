#pragma once
#include"BULLET_BASE.h"
#include "PLAYER.h"


namespace GAME02 {
	class EBULLET:public BULLET_BASE
	{
	private:
		float deg;
	public:        
		void init();
		void create();
		void update();
		void draw();
		void shoot(int x, int y);
		bool hit(PLAYER& player);

		float left();
		float right();
		float top();
		float bottom();
	};
}
