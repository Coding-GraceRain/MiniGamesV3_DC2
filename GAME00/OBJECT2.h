#pragma once
namespace GAME00
{
	class OBJECT2
	{
	private:
		int Img;
		int FallImg;
		float Px, Py;
		float StartX, StartY;

		//落下床
		bool IsFall;       //落下床か
		bool IsFalling;    //今落ちているか
		float FallSpeed;

		//移動床
		bool IsMove;
		int MoveDir;   //どの方向に動くか　1なら右　‐1なら左
		float MoveSpeed;
	public:
		void create();
		void init(float x, float y, bool falling, bool move);
		void startfall();
		void startmove();
		void update();
		void moveY(float dy);
		void draw();

		float left();
		float right();
		float top();
		float bottom();


		//----------------------------------------------------------------
		//デバッグ用
		/*
			void drawDebugNum(int num);
		*/
		//----------------------------------------------------------------
	};
}
