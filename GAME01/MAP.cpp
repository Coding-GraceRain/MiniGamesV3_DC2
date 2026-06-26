#include"GAME.h"
#include"MAP.h"
#include"CELL.h"
#include"PERSENT.h"
#include<random>
namespace GAME01
{
	MAP::~MAP() {
		player = nullptr;
		game = nullptr;
		destroy();
	}
	void MAP::create() {
		level = 0;
		//マップの横のマス数 ＋両端を壁
		Col = 20 + 2;
		//マップの縦のマス数　＋両端を壁
		Row = 15 + 2;
		GridSize = 50;

		MapCol = Col * GridSize;
		MapRow = Row * GridSize;
		//Initial(初期)マップ左上の座標の設定
		IPx = (width - MapCol) / 2;
		IPy = (height - MapRow) / 2;
		//マップのすべてのマス数
		MapSize = Col * Row;
		//Cell[][]のそれぞれの数の設定
		Cell = new CELL * [Col];
		for (int c = 0;c < Col;c++) {
			Cell[c] = new CELL[Row];
		}
		//各マスの設定(床、壁、座標)
		for (int c = 0;c < Col;c++) {
			for (int r = 0;r < Row;r++) {
				//type 0=床 1=壁 2=自機 3=敵の初期位置 4=階段 5=宝箱
				if (c == 0 || r == 0 || c == Col - 1 || r == Row - 1) {
					Cell[c][r].type = 1;
				}
				else {
					Cell[c][r].type = 0;
				}
				//座標設定
				Cell[c][r].Px = (IPx + (c * GridSize));
				Cell[c][r].Py = (IPy + (r * GridSize));
			}
		}
		makeStairs();
		makeEnemy();
	}
	void MAP::init() {
		//各マスの設定(床、壁、座標)
		for (int c = 0;c < Col;c++) {
			for (int r = 0;r < Row;r++) {
				//type 0=床 1=壁 2=自機 3=敵 4=階段
				if (c == 0 || r == 0 || c == Col - 1 || r == Row - 1) {
					Cell[c][r].type = 1;
				}
				else {
					Cell[c][r].type = 0;
				}
				//座標設定
				Cell[c][r].Px = (IPx + (c * GridSize));
				Cell[c][r].Py = (IPy + (r * GridSize));
			}
		}
	}
	void MAP::destroy() {
		for (int c = 0;c < Col;c++) {
			delete[]Cell[c];
		}
		delete[] Cell;
		Cell = nullptr;
	}
	void MAP::makeStairs() {
		if (level % 50 == 49) { Cell[11][15].type = 4; }
		else{
			int StairsPx = customrand(1, 20);
			int StairsPy = customrand(1, 15);
			while (Cell[StairsPx][StairsPy].type != 0) {
				int StairsPx = customrand(1, 20);
				int StairsPy = customrand(1, 15);
			}
			Cell[StairsPx][StairsPy].type = 4;
		}
		ExistenceStairs = true;
	}
	void MAP::makeEnemy() {
		for (auto e : game->enemies) {
			delete e;
		}
		game->enemies.clear();
		enemyPx = customrand(1, 20);
		enemyPy = customrand(1, 15);
		while (Cell[enemyPx][enemyPy].type != 0) {
			enemyPx = customrand(1, 20);
			enemyPy = customrand(1, 15);
		}
		Cell[enemyPx][enemyPy].type = 3;
		//敵の種類決め
		int type = decideEnemyType();
		Cell[enemyPx][enemyPy].enemyType = type;
		ExistenceEnemy = true;
	}
	void MAP::makeBoss() {
		for (auto e : game->enemies) {
			delete e;
		}
		game->enemies.clear();
		Cell[11][1].type = 7;
		ExistenceEnemy = true;
	}
	void MAP::update() {
		clear(0);
		collectenemyExp = 0;
		level++;
		init();
		numberOfEnemy = (rand() % 3 + 1)+(int)(level/30);
		PlayerPx = (player->getPx() - IPx) / GridSize;
		PlayerPy = (player->getPy() - IPy) / GridSize;
		Cell[PlayerPx][PlayerPy].type = 2;
		makeStairs();
		for (int i = 0;i < numberOfEnemy;i++) { makeEnemy(); }
	}
	void MAP::generateRestArea() {
		nowRestArea = true;
		clear(75, 255, 0);
		collectenemyExp = 0;
		init();
		PlayerPx = (player->getPx() - IPx) / GridSize;
		PlayerPy = (player->getPy() - IPy) / GridSize;
		Cell[PlayerPx][PlayerPy].type = 2;
		int randPx = customrand(1, 20);
		int randPy = customrand(1, 5);
		while (Cell[randPx][randPy].type != 0&&randPx==PlayerPx) {
			randPx = customrand(1, 20);
			randPy = customrand(1, 5);
		}
		Cell[randPx][randPy].type = 5;
		Cell[randPx][randPy + 5].type = 6;
		makeStairs();
	}
	void MAP::generateBossArea() {
		nowBossArea = true;
		clear(90,0,143);
		collectenemyExp = 0;
		level++;
		init();
		PlayerPx = (player->getPx() - IPx) / GridSize;
		PlayerPy = (player->getPy() - IPy) / GridSize;
		Cell[PlayerPx][PlayerPy].type = 2;
		makeBoss();
		makeStairs();
	}
	void MAP::draw() {
		fill(255);
		textSize(GridSize);
		for (int c = 0;c < Col;c++) {
			for (int r = 0;r < Row;r++) {
				if (Cell[c][r].type == 1) {
					::text("壁", Cell[c][r].Px, Cell[c][r].Py);
				}
				if (Cell[c][r].type == 4) {
					if (game->allEnemiesDefeated())::text("次", Cell[c][r].Px, Cell[c][r].Py);
				}
				if (Cell[c][r].type == 5) {
					::text("癒", Cell[c][r].Px, Cell[c][r].Py);
				}
				if (Cell[c][r].type == 6) {
					::text("強", Cell[c][r].Px, Cell[c][r].Py);
				}
			}
		}
	}
	 int MAP::decideEnemyType() {
		int base = (int)(level / 10) + 1;
		int phase = (int)(level % 10);
		int persent = rand100();
		if (phase <5) {
			if (persent <= 100 - (phase * 5))return base;
			else return base + 1;
		}
		else {
			if (persent <= 75 - ((phase - 5) * 5))return base;
			else if (persent <= 75 - ((phase - 5) * 5)
				+ 25 + ((phase - 5) * 3))return base + 1;
			else return base + 2;
		}
	}
}