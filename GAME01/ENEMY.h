#pragma once
#include "CHARACTER.h"
namespace GAME01
{
	class PLAYER;
	class MAP;

	class ENEMY :
		public CHARACTER
	{
	protected:
		int rewardExp;
		
	public:
		PLAYER* player;
		MAP* map;
		virtual ~ENEMY();
		virtual void init(int IPx, int IPy);
		virtual void draw();
		virtual void update();
		virtual void statusdraw();
		virtual void move();
		virtual void actUP();
		virtual void actLEFT();
		virtual void actDOWN();
		virtual void actRIGHT();
		virtual bool canMoveUP();
		virtual bool canMoveLEFT();
		virtual bool canMoveDOWN();
		virtual bool canMoveRIGHT();
		void knockBack();
		float getstep() { return size*n.SIZ; }
		float getHp() { return n.HP; }
		void setHp(float dmg) {
			float Dmg = dmg * (100.0f / (100.0f + n.DEF));
			if (Dmg < 0.5)Dmg = 0.5f;
			n.HP -= Dmg;
			if (n.HP <= 0) {
				isAlive = false;
				map->collectExp(rewardExp);
			}
		}
		bool attacking = false;
		bool acted = false;
		//Adjacent = 隣接
		bool AdjacentAnotherEnemyUP;
		bool AdjacentAnotherEnemyLEFT;
		bool AdjacentAnotherEnemyDOWN;
		bool AdjacentAnotherEnemyRIGHT;
		bool nowLaunch;
	};
}
