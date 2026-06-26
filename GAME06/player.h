#pragma once
#include"ITEM.h"
namespace GAME06
{
	class PLAYER
	{
	private:
		int Img = 0;
		int Sound = 0;
		int Sound2 = 0;
		float Px = 0, Py = 0;
		float Pvx = 0, Pvy = 0;
	public:
		char a[40];
		int Timer = 0;
		int Score = 0;
		int Get = 0;
		void init();
		void create();
		void update();
		void draw();
		void score();
		float left() { return Px - 50; }
		float right() { return Px + 50; }
		float top() { return Py - 35; }
		float bottom() { return Py + 35; }
		bool hit(ITEM& item);
	};
}