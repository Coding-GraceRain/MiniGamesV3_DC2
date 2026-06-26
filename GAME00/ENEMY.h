#pragma once
#include"BULLET.h"
namespace GAME00
{
	class ENEMY
	{
	private:
		int Img;
		int ImgRight;
		float Px, Py;
		float Vx, Vy;
		static const int Bullet_Max = 10;
		BULLET Bullet[Bullet_Max];
		float ShotTimer;
	public:
		void create();
		void init(float x, float y);
		void update();
		void moveY(float dy);
		void moveBulletY(float dy);
		void draw();
		bool isRight;

		float left();
		float right();
		float top();
		float bottom();
		BULLET& getbullet(int i);
	};
}
