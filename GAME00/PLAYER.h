#pragma once
#include"OBJECT.h"
#include"OBJECT2.h"
#include "ENEMY.h"
namespace GAME00
{
	class PLAYER
	{
	private:
		int Img;
		int JumpSe;
		int DamageSe;
		float Px, Py;
		float Vx, Vy;
		float Gravity;
		int JumpCount;
		const int Max_Jump = 2;
		bool OnGround;     //�n�ʂɏ���Ă��邩
		float StartX, StartY;
		int Hp;
		int MaxHp;
		float DamageTimer;
	public:
		void create();
		void destroy();
		void init();
		void saveStartPos();
		void returnToStart();
		void update();
		void moveY(float dy);
		void draw();
		int getHp();
		void damage(int value);
		void respawn();


		float left();
		float right();
		float top();
		float bottom();
		bool hit(ENEMY& enemy);
		bool hit(OBJECT& object);
		bool landOn(OBJECT& object);    //landOn:���n������
		bool hit(OBJECT2& object2);
		bool hitCeiling(OBJECT2& object2);
		bool hitSide(OBJECT2& object2);
		bool landOn(OBJECT2& object2);
		bool hit(BULLET& bullet);
		bool isDead();
		bool isDamage();
	};
}
