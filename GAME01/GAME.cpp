#include "GAME.h"
#include "GAME01.h"
#include"CHARACTER.h"
#include"UserInterface.h"
#include<time.h>
#include<string>
namespace GAME01
{
	GAME1::GAME1(MAIN*m) :player(nullptr), map(nullptr), UI(nullptr),game01(nullptr),main(m){
	}
	GAME1::~GAME1() {
		delete player;
		player = nullptr;
		for (int i = 0;i < (int)enemies.size();i++) {
			delete enemies[i];
			enemies[i] = nullptr;
		}
		delete map;
		map = nullptr;
		delete UI;
		UI = nullptr;
	}
	void GAME1::create() {
		srand((unsigned int)time(NULL));
		player = new PLAYER;
		map = new MAP;
		UI = new UserInterface;
		map->player = player;
		map->game = this;
		player->map = map;
		player->UI = UI;
		player->game = this;
		UI->player = player;
		UI->game = this;
		map->create();
		spawnEnemy();
		player->create();
		UI->init();
		STATE = TITLE;
	}
	void GAME1::title() {
		clear(100, 100, 100);
		std::string s[] = { 
			"ROGUE",
			"PLAY",
			"TUTORIAL",
			"EXIT",
		};
		int textsize = 100;
		int count = std::size(s);
		for (int i = 0;i < count;i++) {
			fill(255);
			if (i != 0)textsize = 75;
			if (i == 0)textsize = 100;
			if (i == choiceCursor) fill(255, 0, 0);
			textSize(textsize);
			float drawx = width / 2.0f - s[i].size() * textsize * 0.25f;
			text(s[i].c_str(), drawx, (i + 1) * 200);
		}
		fill(255);
		std::string t = "↑↓キーで選択";
		text(t.c_str(), width - ((t.size() / 2) * textsize) - 20, height - textsize);
		text("ENTERで確定", textsize, height - textsize);
		if (isTrigger(KEY_UP))choiceCursor--;
		if (isTrigger(KEY_DOWN))choiceCursor++;
		if (choiceCursor < 1)choiceCursor = std::size(s) - 1;
		if (choiceCursor > std::size(s) - 1)choiceCursor = 1;
		if (isTrigger(KEY_ENTER)) {
			switch (choiceCursor) {
			case 1:
				STATE = PLAY;
				break;
			case 2:
				STATE = TUTORIAL;
				break;
			case 3:
				game01->backToMenu();
				break;
			}
		}
	}
	void GAME1::tutorial() {
		clear(0);
		int textsize = 50;
		textSize(textsize);
		const int num = 7;
		std::string t[num];
		t[0] = "WASDキーで移動";
		t[1] = "敵と隣接している状態で敵に向かって移動で攻撃";
		t[2] = "Eキーでステータス等のメニューを表示";
		t[3] = "敵がいる状態でSPACEキーでその場にとどまり、１回復";
		t[4] = "levelUp時に報酬３種のうちから１つを選択、背景色は報酬のランクを表す";
		t[5] = "5の倍数階クリア時、確率で休憩エリアへ、進むほど確率が下がっていく";
		t[6] = "50の倍数階はボスエリアとなっている";
		for (int i = 0;i < num;i++) {
			float drawx = width / 2.0f - t[i].size() * textsize * 0.25f;
			text(t[i].c_str(),drawx, (i + 1) * 100);
		}
		text("SHIFT+ENTERでタイトル画面へ", textsize, height - textsize);
		if (isPress(KEY_SHIFT)&&isTrigger(KEY_ENTER)) { STATE = TITLE; }
	}
	void GAME1::play() {
		if (openUI) {
			UI->openUI();
			return;
		}
		if (bossDefeated) {
			if (!initCursor) {
				choiceCursor = 0;
				initCursor = true;
			}
			askContinue();
			return;
		}
		if (allocate) {
			player->restAreaPowerUp();
			return;
		}
		if (getRewardMode) {
			player->drawReward(player->rewardStatus, player->rewardContens, player->RewardRank);
			player->choiceReward(player->rewardStatus, player->rewardContens);
			return;
		}
		knockbackFlag = false;
		bool nowKnockback = false;
		bool knockFinished = false;
		clear(0);
		if (map->nowRestArea)clear(75, 255, 0);
		else if (map->nowBossArea)clear(90, 0, 143);
		map->draw();
		textSize(40);
		std::string s1 = "MAPlevel:" + std::to_string((float)map->getmapLevel());
		text(s1.c_str(), 10, 40);
		//ノックバック中ならその処理して終了
		if (player->knockTimer > 0) {
			player->knockBack();
			nowKnockback = true;
			if (player->knockTimer == 0)knockFinished = true;
		}
		for (auto e : enemies) {
			if (e != nullptr && e->knockTimer > 0) {
				e->knockBack();
				nowKnockback = true;
				if (e->knockTimer == 0)knockFinished = true;
			}
		}
		if (nowKnockback) {
			for (auto e : enemies)e->draw();
			player->draw();
			return;
		}
		if (trunchangeTimer > 0) {
			trunchangeTimer--;
			canUpdate = false;
		}
		else if (!knockbackFlag) {
			canUpdate = true;
		}
		//行動
		if (!knockbackFlag) {
			if (!enemyTrunFlag && canUpdate) { player->update(); }
			else if (enemyTrunFlag && canUpdate) {
				for (int i = 0;i < (int)enemies.size();i++) {
					enemies[i]->update();
				}
			}
		}
		if (enemyTrunFlag) {
			bool allacted = true;
			for (auto e : enemies) {
				if (e != nullptr && e->isAlive) {
					if (!e->acted || e->knockTimer > 0) {
						allacted = false;
					}
				}
			}
			if (allacted) {
				for (auto e : enemies) {
					if (e != nullptr)e->acted = false;
				}
				trunchangerequest();
			}
		}
		player->draw();
		for (int i = 0;i < (int)enemies.size();i++) {
			if (enemies[i] != nullptr && enemies[i]->isAlive)enemies[i]->draw();
		}
		player->statusdraw();
		enemies[0]->statusdraw();
		//ターンチェンジ処理
		if (trunchangeFlag) {
			if (player->knockTimer > 0) return;
			for (int i = 0; i < (int)enemies.size(); i++) {
				if (enemies[i] != nullptr && enemies[i]->knockTimer > 0) return;
			}
			//全部死んでたら常にプレイヤーターン
			if (allEnemiesDefeated()) {
				enemyTrunFlag = false;
				trunchangeFlag = false;
				return;
			}
			enemyTrunFlag = !enemyTrunFlag;
			trunchangeTimer = 15;
			trunchangeFlag = false;
			for (auto e : enemies) {
				e->attacking = false;
			}
		}
		if (!player->isAlive)STATE = GAMEOVER;
	}
	void GAME1::gameover() {
		clear(100);
		textSize(100);
		std::string s = "到達階層：" + std::to_string((int)map->getmapLevel());
		text(s.c_str(), width / 2 - (((float)s.size()/2) * 100), 300);
		text("Rキーでタイトルに戻る", width / 2 - 600, 500);
		if (isTrigger(KEY_R)) { 
			
			STATE = TITLE;
		}
	}
	void GAME1::score() {

	}
	void GAME1::proc() {
			if (STATE == TITLE) {
				title();
			}
			if (STATE == TUTORIAL) {
				tutorial();
			}
			else if (STATE == PLAY) {
				play();
			}
			else if (STATE == GAMEOVER) {
				gameover();
			}
			else if (STATE == SCORE) {
				score();
			}
	}
	void GAME1::trunchangerequest() {
		trunchangeFlag = true;
	}
	void GAME1::enemyTCrQ() {
		requestEnemy += 1;
		if (requestEnemy == enemies.size()) {
			requestEnemy = 0;
			trunchangeFlag = true;
		}
		return;
	}
	void GAME1::spawnEnemy() {
		for (auto e : enemies) {
			delete e;
		}
		enemies.clear();
		for (int c = 0; c < map->getCol(); c++) {
			for (int r = 0; r < map->getRow(); r++) {
				if (map->Cell[c][r].type == 3) {
					if (map->Cell[c][r].enemyType == 1) {
						ENEMY* e = new WEAKENEMY;
						e->map = map;
						e->player = player;
						e->game = this;
						e->init(c, r);
						enemies.push_back(e);
					}
					else if (map->Cell[c][r].enemyType == 2) {
						ENEMY* e = new NORMALENEMY;
						e->map = map;
						e->player = player;
						e->game = this;
						e->init(c, r);
						enemies.push_back(e);
					}
					else if (map->Cell[c][r].enemyType == 3) {
						ENEMY* e = new THIRDENEMY;
						e->map = map;
						e->player = player;
						e->game = this;
						e->init(c, r);
						enemies.push_back(e);
					}
					else if (map->Cell[c][r].enemyType == 4) {
						ENEMY* e = new FOURTHENEMY;
						e->map = map;
						e->player = player;
						e->game = this;
						e->init(c, r);
						enemies.push_back(e);
					}
					else if (map->Cell[c][r].enemyType == 5) {
						ENEMY* e = new FIFTHENEMY;
						e->map = map;
						e->player = player;
						e->game = this;
						e->init(c, r);
						enemies.push_back(e);
					}
					else if (map->Cell[c][r].enemyType == 6) {
						ENEMY* e = new SIXTHENEMY;
						e->map = map;
						e->player = player;
						e->game = this;
						e->init(c, r);
						enemies.push_back(e);
					}
					else if (map->Cell[c][r].enemyType == 7) {
						ENEMY* e = new SEVENTHENEMY;
						e->map = map;
						e->player = player;
						e->game = this;
						e->init(c, r);
						enemies.push_back(e);
					}
					else {
						ENEMY* e = new ENEMY;
						e->map = map;
						e->player = player;
						e->game = this;
						e->init(c, r);
						enemies.push_back(e);
					}
				}
				else if(map->Cell[c][r].type==7) {
					ENEMY* e = new BOSS;
					e->map = map;
					e->player = player;
					e->game = this;
					e->init(c, r);
					enemies.push_back(e);
				}
			}
		}
	}
	bool GAME1::allEnemiesDefeated() {
		for (int i = 0;i < (int)enemies.size();i++) {
			if (enemies[i] != nullptr) { if (enemies[i]->isAlive) { return 0; } }
		}
		return 1;
	}
	void GAME1::knockback(int direction, CHARACTER* chara) {
		knockbackFlag = true;
		switch (direction) {
		case 1:
			//戻るための数値設定
			chara->setKnockVy(+(map->getGridSize() / 10));
			chara->setKnockVx(0);
			break;
		case 2:
			//戻るための数値設定
			chara->setKnockVx(+(map->getGridSize() / 10));
			chara->setKnockVy(0);
			break;
		case 3:
			//戻るための数値設定
			chara->setKnockVy(-(map->getGridSize() / 10));
			chara->setKnockVx(0);
			break;
		case 4:
			//戻るための数値設定
			chara->setKnockVx(-(map->getGridSize() / 10));
			chara->setKnockVy(0);
			break;
		}
	}
	bool GAME1::occupied(int x, int y, ENEMY* me) {
		for (auto e : enemies) {
			if (!e->isAlive)continue;
			if (e == me)continue;
			if (e->getPCellx() == x && e->getPCelly() == y) {
				return true;
			}
		}
		return false;
	}
	void GAME1::askContinue(){
		clear(249,255,73);
		textSize(75);
		std::string ask[2];
		ask[0] = "タイトルに戻る";
		ask[1] = "さらに先へ進む";
		for (int i = 0;i < 2;i++) {
			if (i == choiceCursor)fill(255, 0, 0);
			else fill(255);
			text(ask[i].c_str(), width / 2 + ((((float)ask[i].size()) * 50) * (-1 + i)), 700);
		}
		if (isTrigger(KEY_RIGHT))choiceCursor++;
		if (isTrigger(KEY_LEFT))choiceCursor--;
		if (choiceCursor < 0)choiceCursor = 1;
		if (choiceCursor > 1)choiceCursor = 0;
		if (isTrigger(KEY_ENTER)) {
			initCursor = false;
			if (choiceCursor == 0) {
				choiceCursor = 1;
				STATE = TITLE;
			}
			else { 
				clear(0);
				player->goNextLevel(); 
			}
		}
		if (isTrigger(KEY_E)) {
			UI->setindex(1);
			openUI = true;
		}
		fill(255);
		std::string s = "到達階層：" + std::to_string((int)map->getmapLevel());
		text(s.c_str(), width / 2 - (((float)s.size() / 2) * 50), 300);
		text("Eキーでステータス等の表示", 10, height - 100);
	}
}