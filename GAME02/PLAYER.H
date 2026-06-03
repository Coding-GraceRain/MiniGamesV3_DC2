#pragma once
#include"ENEMY.h"
namespace GAME02
{
	class PLAYER {
	private:
		int Img;
	public:
		float Px, Py, Vx, Vy;
		int Bom;
		int Shotlevel;
		void create();
		void init();
		void update();
		void draw();
		void sibariupdate();
		
		float left();
		float right();
		float top();
		float bottom();

		bool hit(ENEMY& enemy);
	};
}