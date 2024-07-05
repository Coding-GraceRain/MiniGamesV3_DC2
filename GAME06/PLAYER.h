#pragma once
namespace GAME06 
{
	class PLAYER
	{
	private:
		float Px = 0, Py = 0, W = 0, H = 0, Vx = 0, OfsY = 0;
		int Hp = 0;
	public:
		PLAYER();
		~PLAYER();
		void init();
		void update();
		void draw();
		void proc();
		float px() { return Px; }
		float py() { return Py; }
		float w() { return W; }
		float h() { return H; }
		float ofsY() { return OfsY; }
		int& hp() { return Hp; }
	};
}
