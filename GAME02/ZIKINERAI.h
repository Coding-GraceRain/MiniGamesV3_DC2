#pragma once
#include"BULLET_BASE.h"
#include "PLAYER.H"
#include "ENEMY3.h"
namespace GAME02 {
	class ZIKINERAI :public BULLET_BASE
	{
	private:
		float deg;
	public:
		void init();
		void create();
		void update();
		void draw();
		void shoot(PLAYER&,ENEMY3&);
		bool hit(PLAYER&);

		float left();
		float right();
		float top();
		float bottom();
	};
}

