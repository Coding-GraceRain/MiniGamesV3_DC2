#pragma once
#include<vector>
#include "CELL.h"
namespace GAME01
{
	class PLAYER;
	class ENEMY;
	class GAME1;

	class MAP
	{
	public:
		PLAYER* player;
		GAME1* game;
		~MAP();
		void init();
		void create();
		void update();
		void draw();
		void destroy();
		void makeStairs();
		void makeEnemy();
		void makeBoss();
		void generateRestArea();
		void generateBossArea();
		int decideEnemyType();
		int getIPx() { return IPx; }
		int getIPy() { return IPy; }
		int getCol() { return Col; }
		int getRow() { return Row; }
		int getGridSize() { return GridSize; }
		int getmapLevel() { return level; }
		int getNoe() { return numberOfEnemy; }
		int getenemyExp() { return collectenemyExp; }
		void collectExp(int enemyExp) { collectenemyExp += enemyExp; }
		CELL** Cell;
		bool nowRestArea;
		bool nowBossArea;
	private:
		int IPx, IPy;
		int PlayerPx, PlayerPy;
		int enemyPx, enemyPy;
		int Col, Row;
		int GridSize;
		int MapCol, MapRow;
		int MapSize;
		int level;
		int collectenemyExp;
		int numberOfEnemy = (rand() % 3) + 1;
		//Existence = 存在
		bool ExistenceStairs = false;
		bool ExistenceEnemy = false;
	};
}