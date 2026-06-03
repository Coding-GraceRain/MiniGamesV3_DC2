#pragma once
namespace GAME02 {
	class SHOTPOINT
	{
	private:
		int Img;
		float Deg;
	public:
		bool Alive;
		float Px, Py;
		void create();
		void init();
		void setPosition(float px, float py);
		void draw();
	};
}

