#pragma once
#include"ENEMY.h"
#include"BULLET_BASE.h"
#include "ENEMY3.h"
namespace GAME02 {
	class BULLET:public BULLET_BASE
	{
	public:
		float Delay;
		void init();
		void create();
		void update();
		void draw();
		void shoot(int x, int y);
		bool hit(ENEMY& enemy);
		bool hit(ENEMY3& enemy);

		float left();
		float right();
		float top();
		float bottom();

	};
}


