#pragma once
namespace GAME00
{
	class OBJECT
	{
	private:
		int Img;
		float Px, Py;
	public:
		void create();
		void init();
		void moveY(float dy);
		void draw();

		float left();
		float right();
		float top();
		float bottom();
	};
}
