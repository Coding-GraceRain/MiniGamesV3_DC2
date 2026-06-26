#pragma once
namespace GAME00
{
	class FLAG
	{
	private:
		int Img;
		float Px, Py;
	public:
		void create();
		void init();
		void moveY(float dy);
		void draw(float scrollY);

		float left();
		float right();
		float top(float scrollY);
		float bottom(float scrollY);
	};
}
