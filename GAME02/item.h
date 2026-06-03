#pragma once
#include"PLAYER.h"
namespace GAME02 {
	class ITEM
	{
	private:
		int Img;
		float Px, Py;
		float Vx;
	public:
		bool Alive;
		
		void init();
		void create();
		void update();
		void draw();
		void set(int x,int y);

		float left();
		float right();
		float top();
		float bottom();
		bool hit(PLAYER& p);
		

	};
}