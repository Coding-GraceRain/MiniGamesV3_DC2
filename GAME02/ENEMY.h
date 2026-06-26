#pragma once
#include"ENEMY_BASE.h"
namespace GAME02 {

	class ENEMY : public ENEMY_BASE{
	public:
		bool hit(ENEMY& enemy);
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
	};
}
