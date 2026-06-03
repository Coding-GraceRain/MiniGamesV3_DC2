#pragma once
#include"BULLET_BASE.h"
#include "PLAYER.H"
#include "BULLET.h"
#include "ENEMY2.h"
namespace GAME02 {
	class BBULLET 
		:public BULLET_BASE
	{		
	public:
		BOSS Boss;
		void init();
		void create();
		void update();
		void draw();
		void set(float x, float y, float vx, float vy);
		void shoot();
		bool hit(PLAYER& player);

		float left();
		float right();
		float top();
		float bottom();
	};
}

