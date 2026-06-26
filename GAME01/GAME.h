#pragma once
#include<vector>
#include"PLAYER.h"
#include"ENEMY.h"
#include"WEAKENEMY.h"
#include"NORMALENEMY.h"
#include"THIRDENEMY.h"
#include"FOURTHENEMY.h"
#include"FIFTHENEMY.h"
#include"SIXTHENEMY.h"
#include"SEVENTHENEMY.h"
#include"BOSS.h"
#include"UserInterface.h"
#include"../MAIN/MAIN.h"
#include"MAP.h"
namespace GAME01
{
	class GAME;

	class GAME1
	{
	private:
		int STATE;
		enum { TITLE, TUTORIAL, PLAY, GAMEOVER, SCORE };
		int requestEnemy = 0;
		float trunchangeTimer;
		float knockVx = 0;
		float knockVy = 0;
		int knockTimer = 0;
		int Delay = 5;
		int choiceCursor = 1;
		int tutorialnumber = 1;
		bool initCursor = false;
	public:
		PLAYER* player;
		std::vector<ENEMY*> enemies;
		WEAKENEMY* weakenemy;
		NORMALENEMY* normalenemy;
		THIRDENEMY* thirdenemy;
		FOURTHENEMY* fourthenemy;
		FIFTHENEMY* fifthenemy;
		SIXTHENEMY* sixthenemy;
		SEVENTHENEMY* seventhenemy;
		BOSS* boss;
		MAP* map;
		UserInterface* UI;
		MAIN* main;
		GAME* game01 = nullptr;
		GAME1(MAIN*m);
		~GAME1();
		void create();
		void spawnEnemy();
		void title();
		void tutorial();
		void play();
		void gameover();
		void score();
		void proc();
		void trunchangerequest();
		void enemyTCrQ();
		void askContinue();//ask　＝　尋ねる
		void knockback(int direction, CHARACTER* chara);//direction=方向　1=上　2=左　3=下　4=右
		void setState(int state) { STATE = state; }
		bool allEnemiesDefeated();
		bool occupied(int x,int y,ENEMY*me);
		bool canUpdate;
		bool enemyTrunFlag = false;
		bool trunchangeFlag = false;
		bool firstEnemySpawn = true;
		bool knockbackFlag = false;
		bool getRewardMode = false;
		bool openUI = false;
		bool allocate = false;
		bool bossDefeated = false;
		int getDelay() { return Delay; }
	};
}