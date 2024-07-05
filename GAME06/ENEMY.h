#pragma once
namespace GAME06 
{
	class ENEMY
	{
	private:
		float Px = 0, Py = 0, W = 0, H = 0, Angle = 0, OfsY = 0, AngleSpeed = 0;
		int Hp = 0;
	public:
		ENEMY();
		~ENEMY();
		void init();
		void update();
		void draw();
		float px() { return Px; }
		float py() { return Py; }
		float w() { return W; }
		float h() { return H; }
		float ofsY() { return OfsY; }
		int& hp() { return Hp; }
	};
}

