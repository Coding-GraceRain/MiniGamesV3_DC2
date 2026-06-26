#pragma once
#include"CHARACTER.h"
#include"PERSENT.h"
namespace GAME01
{
	//前方宣言というやつらしい
	class ENEMY;
	class MAP;
	class UserInterface;

	class PLAYER :
		public CHARACTER
	{
	protected:
		int surroundings;//周辺、周囲
		int level = 1;
		int Exp;
		int choiceCursor = 1;
		const int rewardCount = 3;
		int maxAllocatePoint = 0;
		int index = 1;//休憩エリアでの強化関係のアレ
		int MAllocateP = 0;
		float nowStatus[7];
		enum reward { statusUp, special };
	public:
		MAP* map;
		UserInterface* UI;
		~PLAYER();
		void init();
		void draw();
		void update();
		void move();
		void statusdraw();
		void knockBack();
		void getExp();
		void decideReward(int rewardRank);
		//decide = 決める
		int decideRewardRank(int maplevel);
		void drawReward(int rewardStatus[], float rewardContens[], int rewardRank);
		void choiceReward(int rewardStatus[], float rewardContens[]);
		void restAreaPowerUp();
		void goNextLevel();
		float getstep() { return step; }
		float getHp() { return n.HP; }
		float getMaxHp() { return MaxHp; }
		float getSTR() { return n.STR; }
		float getDEF() { return n.DEF; }
		float getINT() { return n.INT; }
		float getDEX() { return n.DEX; }
		float getLUC() { return n.LUC; }
		int getHPAbsorption() { return HPAbsorptionEffect; }
		void setchoiceCursor(int n) { choiceCursor = n; }
		void setHp(float dmg) {
			float Dmg = dmg * (100.0f / (100.0f + n.DEF));
			if (Dmg < 0.5)Dmg =0.5f;
			n.HP -= Dmg;
		}
		int rewardStatus[3];//upStatus or special special=0;
		float rewardContens[3];//上昇量かスペシャルの内容
		bool NoReroll = true;
		bool decidereward;
		bool drawreward;
		int RewardRank = 1;//1=白　2=緑　3=青　4=紫　5=金
	};
}
