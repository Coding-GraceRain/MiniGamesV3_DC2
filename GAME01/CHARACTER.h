#pragma once
#include<cmath>
#include "../../libOne/inc/libOne.h"
#include"MAP.h"
namespace GAME01
{
	class GAME1;
	class map;

	class CHARACTER
	{
	protected:
		//位置
		float Px, Py;
		int PCellx = 0, PCelly = 0;
		//基本サイズ
		float size;
		//グリッド
		float step = 0;
		//ステータス
		struct status {
			float HP, STR, DEF, DEX, INT, LUC, SIZ;
			status()
				:HP(0), STR(0), DEF(0), DEX(0), INT(0), LUC(0), SIZ(1)
			{
			}
		};
		bool criticalHit = false;
		float MaxHp;
		enum dir { up, down, left, right };
		int direction = 0;//direction=方向　1=上　2=左　3=下　4=右
	public:
		status n;
		GAME1* game;
		MAP* map;
		virtual void create();
		virtual void init();
		virtual void draw();
		virtual void update();
		virtual void knockBack();
		float HPAbsorptionEffect = 0;
		bool isAlive = true;
		//こちらが真下にいる判定
		bool enemyUp(CHARACTER* ME, CHARACTER* YOU, float step);
		//こちらが真上にいる判定
		bool enemyDawn(CHARACTER* ME, CHARACTER* YOU, float step);
		//こちらが真右にいる判定
		bool enemyLeft(CHARACTER* ME, CHARACTER* YOU, float step);
		//こちらが真左にいる判定
		bool enemyRaight(CHARACTER* ME, CHARACTER* YOU, float step);
		//こちらが真下にいる判定(壁)
		bool objectUp(CHARACTER* ME, MAP* YOU);
		//こちらが真上にいる判定(壁)
		bool objectDawn(CHARACTER* ME, MAP* YOU);
		//こちらが真左にいる判定(壁)
		bool objectRight(CHARACTER* ME, MAP* YOU);
		//こちらが真右にいる判定(壁)
		bool objectLeft(CHARACTER* ME, MAP* YOU);
		virtual float getPx() { return Px; }
		virtual float getPy() { return Py; }
		virtual int getPCellx() { return PCellx; }
		virtual int getPCelly() { return PCelly; }
		virtual void setPx(float Vx) { Px += Vx; }
		virtual void setPy(float Vy) { Py += Vy; }
		virtual void setKnockVx(float Vx) { knockVx = Vx; }
		virtual void setKnockVy(float Vy) { knockVy = Vy; }
		virtual void setHp(float dmg) { n.HP -= (dmg - ((float)n.DEF / 4.0f)); }
		virtual void healHp(float heal) {
			this->n.HP += heal;
			if (n.HP > MaxHp) { n.HP = MaxHp; }
		}
		virtual void attack(CHARACTER* ME, CHARACTER* YOU);
		float knockVx = 0;
		float knockVy = 0;
		int knockTimer = 0;
	};
}

