#pragma once
#include "player.h"

namespace GAME04 {
	
	class BULLET {
	public:


		
		int hp = 0;
		float px = 0;
		float py = 0;
		float vy = -20.0f; // ãŒü‚«
		float pr = 15;
		float h = 20;

		void move();
		void draw();
		void shoot(float x, float y);

	};

}