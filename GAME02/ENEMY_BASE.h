#pragma once
namespace GAME02 {
	class ENEMY_BASE
	{
	protected:
		int Img;
	public:
		float Px, Py, Vx, Vy;
		int Cum, Rnd;
		int Hp;
		bool Alive;
		float Delay;
	};
}

