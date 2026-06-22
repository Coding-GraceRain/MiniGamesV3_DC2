#pragma once
#include"ENEMY_BASE.h"
#include "ENEMY.h"
namespace GAME02 {
	class ENEMY3
		:public ENEMY_BASE
	{
	public:
		void create();
		void init();
		void update();
		void draw();
		bool drop();
		bool harddrop();

		float left();
		float right();
		float top();
		float bottom();

		bool hit(ENEMY3& enemy);
		bool hit(ENEMY&);
	};
}