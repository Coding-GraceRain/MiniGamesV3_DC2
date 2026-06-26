#pragma once
namespace GAME00
{
	class BULLET
	{
	private:
		int Img;
		float Px, Py;
		float Vx, Vy;
		float BaseX;
		float Timer;
		bool Active;
	public:
		void create();
		void init(float x, float y, float vx, float vy);
		void update();
		void moveY(float dy);
		void draw();
		void deactivate();
		bool isActive();

		float left();
		float right();
		float top();
		float bottom();
	};
}
