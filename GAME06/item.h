#pragma once
namespace GAME06
{
	class ITEM
	{
	private:
		int Img = 0;
		int Img2 = 0;
	public:
		int I = 0;
		float Ix = 0, Iy = 0;
		float Ivx = 0, Ivy = .0;
		void create();
		void init();
		void update();
		void draw();
		float left() { return Ix - 50; }
		float right() { return Ix + 50; }
		float top() { return Iy - 35; }
		float bottom() { return Iy + 35; }

	};
}