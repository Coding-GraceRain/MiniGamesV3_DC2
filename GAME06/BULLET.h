#pragma once
namespace GAME06 
{
	class BULLET
	{
	protected:
		float Px = 0, Py = 0, W = 0, H = 0, Vx = 0, Vy = 0;
		bool Flag = false;
	public:
		BULLET();
		virtual ~BULLET();
		virtual void init(){}
		virtual void shot(){}
		virtual void draw(){}
		float& px() { return Px; }
		float& py() { return Py; }
		float& w() { return W; }
		float& h() { return H; }
		float& vx() { return Vx; }
		float& vy() { return Vy; }
		bool& flag() { return Flag; }
	};
}
