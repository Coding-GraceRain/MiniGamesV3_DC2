#pragma once
#include "HP_GAUGE.h"
class OBJECT_HP :public HP_GAUGE
{

	public:
		struct DATA {
			int curHp = 0;//表示されるHPの個数
			int MaxNumHp = 0;//表示される最大数
			int My;//敵の下のほうに少しずらすための値
			float increaseHp = 0;//HPの増える幅
			float hpWidth = 0;
			float hpHeight = 0;
		};
	private:
		DATA ObjectGauge;
		float* NowHp;
		float* baseHp;
	public:
		OBJECT_HP(class GAME10_GAME* game);
		~OBJECT_HP();
		void init();
		void appear(int hp, int Level);
		void create();
		void getDamage(float damage, int enemyKind,int weaponKind);
		void death(int i);
		void allDeath();
		void draw(VECTOR2 pos, int enemyKind);
		int GetHp(int i) { return NowHp[i]; }
};

