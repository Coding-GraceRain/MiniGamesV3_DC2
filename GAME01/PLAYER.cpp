#include "PLAYER.h"
#include "GAME.h"
#include"PERSENT.h"
#include"UserInterface.h"
#include<string>
#include<sstream>
#include<iomanip>
namespace GAME01
{
	PLAYER::~PLAYER() {
		game = nullptr;
		map = nullptr;
		UI = nullptr;
	}
	void PLAYER::init() {
		level = 1;
		Px = map->Cell[11][1].Px;
		Py = map->Cell[11][3].Py;
		size = 50;
		n.HP = 20.0f;
		n.STR = 5.0f;
		n.DEF = 3.0f;
		n.INT = 3.0f;
		n.DEX = 3.0f;
		n.LUC = 0.5f;
		n.SIZ = 1;
		MaxHp = n.HP;
		index = 1;
	}
	void PLAYER::draw() {
		if (!isAlive)return;
		textSize(size * n.SIZ);
		text("自", Px, Py);
	}
	void PLAYER::update() {
		n.HP = std::round(n.HP*100.0f)/100.0f;
		if (knockTimer > 0) return;
		knockVx = 0;
		knockVy = 0;
		if (n.HP <= 0) {
			isAlive = false;
			return;
		}
		float step = size * n.SIZ;
		if (!objectUp(this, map) && isTrigger(KEY_W)) {
			bool hitenemy = false;
			direction = 1;
			for (auto e : game->enemies) {
				if (e != nullptr && e->isAlive && enemyUp(this, e, step)) {
					hitenemy = true;
					attack(this, e);
					break;
				}
			}
			if (!hitenemy) { move(); }
			return;
		}
		if (!objectLeft(this, map) && isTrigger(KEY_A)) {
			bool hitenemy = false;
			direction = 2;
			for (auto e : game->enemies) {
				if (e != nullptr && e->isAlive && enemyLeft(this, e, step)) {
					hitenemy = true;
					attack(this, e);
					break;
				}
			}
			if (!hitenemy) { move(); }
			return;
		}
		if (!objectDawn(this, map) && isTrigger(KEY_S)) {
			bool hitenemy = false;
			direction = 3;
			for (auto e : game->enemies) {
				if (e != nullptr && e->isAlive && enemyDawn(this, e, step)) {
					hitenemy = true;
					attack(this, e);
					break;
				}
			}
			if (!hitenemy) { move(); }
			return;
		}
		if (!objectRight(this, map) && isTrigger(KEY_D)) {
			bool hitenemy = false;
			direction = 4;
			for (auto e : game->enemies) {
				if (e != nullptr && e->isAlive && enemyRaight(this, e, step)) {
					hitenemy = true;
					attack(this, e);
					break;
				}
			}
			if (!hitenemy) { move(); }
			return;
		}
		if (isTrigger(KEY_SPACE)) {
			if(!game->allEnemiesDefeated())n.HP += 1;
			if (n.HP > MaxHp)n.HP = MaxHp;
			game->trunchangerequest();
			return;
		}
		if (isTrigger(KEY_E)) {
			UI->setindex(1);
			game->openUI = true;
		}
		if (knockTimer == 0) {
			PCellx = (int)std::round((Px - map->getIPx()) / step);
			PCelly = (int)std::round((Py - map->getIPy()) / step);
			Px = map->getIPx() + PCellx * step;
			Py = map->getIPy() + PCelly * step;
			if (PCellx >= 0 && PCellx < map->getCol() &&
				PCelly >= 0 && PCelly < map->getRow())
			{
				if (game->allEnemiesDefeated() &&
					map->Cell[PCellx][PCelly].type == 4)
				{
					int generationRate = 60 - (map->getmapLevel() * 2);
					if (generationRate < 0)generationRate = 0;
					if (map->getmapLevel() == 50) {
						game->bossDefeated = true;
					}
					else if (map->getmapLevel() % 50 == 49) {
						map->nowRestArea = false;
						getExp();
						map->generateBossArea();
						game->spawnEnemy();
					}
					else if (map->getmapLevel() != 0 && (map->getmapLevel() % 5) == 0 
						&& !map->nowRestArea && rand100() <= (50 + generationRate)) {
						map->nowBossArea = false;
						getExp();
						clear(75, 255, 0);
						map->generateRestArea();
						
					}
					else {
						map->nowRestArea = false;
						map->nowBossArea = false;
						goNextLevel();
					}
				}
				if (map->Cell[PCellx][PCelly].type == 5) {
					map->Cell[PCellx][PCelly].type = 0;
					healHp(MaxHp / 2);
				}
				if (map->Cell[PCellx][PCelly].type == 6) {
					if (game->allocate == false) {
						setchoiceCursor(1);
						maxAllocatePoint = 5+level;
						MAllocateP = maxAllocatePoint;
						nowStatus[0] = n.HP;
						nowStatus[1] = MaxHp;
						nowStatus[2] = n.STR;
						nowStatus[3] = n.DEF;
						nowStatus[4] = n.INT;
						nowStatus[5] = n.DEX;
						nowStatus[6] = n.LUC;
					}
					game->allocate = true;
				}
			}
		}
	}
	void PLAYER::statusdraw() {
		textSize(40);
		std::string s = "PLAYER.HP:" + std::to_string((float)n.HP);
		text(s.c_str(), 500, height - (40 * 2));
		std::string EXP = "level:" + std::to_string(level) + "  EXP:" + std::to_string(Exp)+"/levelupExp:" + std::to_string(level * (10 * 1.5));
		text(EXP.c_str(), 800, 40);
	}
	void PLAYER::move() {
		switch (direction) {
		case 1:
			Py -= map->getGridSize();
			game->trunchangerequest();
			break;
		case 2:
			Px -= map->getGridSize();
			game->trunchangerequest();
			break;
		case 3:
			Py += map->getGridSize();
			game->trunchangerequest();
			break;
		case 4:
			Px += map->getGridSize();
			game->trunchangerequest();
			break;
		}
		direction = 0;
	}
	void PLAYER::knockBack() {
		Px += knockVx;
		Py += knockVy;
		knockTimer--;
		game->knockbackFlag = true;
		if (knockTimer == 0) {
			float step = size * n.SIZ;

			PCellx = (int)std::round((Px - map->getIPx()) / step);
			PCelly = (int)std::round((Py - map->getIPy()) / step);

			Px = map->getIPx() + PCellx * step;
			Py = map->getIPy() + PCelly * step;

			knockVx = 0;
			knockVy = 0;
			game->trunchangerequest();
		}
	}
	void PLAYER::getExp() {
		bool levelup = false;
		decidereward = true;
		drawreward = true;
		Exp += map->getenemyExp();
		if (Exp > (level * (10 * 1.5)-1))levelup = true;
		if (levelup) {
			setchoiceCursor(0);
			MaxHp *= 1.1f;
			n.HP *= 1.1f;
			RewardRank;//1=白　2=緑　3=青　4=紫　5=金
			int maplevel = map->getmapLevel();
			RewardRank = decideRewardRank(maplevel);
			if (decidereward)decideReward(RewardRank);
			game->getRewardMode = true;
			Exp -= (level * (10 * 1.5));
			level++;
		}
		return;
	}
	 int PLAYER::decideRewardRank(int maplevel) {
		int persent = rand1000();
		int rewardRank = 0;
		if (maplevel < 40) {
			if (maplevel % 10 <= 5 && maplevel % 10 != 0) {
				if (persent < 950 - maplevel % 10 * 10) {
					rewardRank = 1 + ceil(maplevel / 10);
				}
				else {
					rewardRank = 2 + ceil(maplevel / 10);
				}
			}
			else if (maplevel % 10 > 5 || maplevel % 10 == 0) {
				if (maplevel % 10 != 0) {
					if (persent < 950 + maplevel % 10 * 10) {
						rewardRank = 1 + ceil(maplevel / 10);
					}
					else if (persent > 990) {
						rewardRank = 3 + ceil(maplevel / 10);
					}
					else {
						rewardRank = 2 + ceil(maplevel / 10);
					}
				}
				else {
					if (persent < 800) {
						rewardRank = 1 + ceil(maplevel / 10);
					}
					else if (persent > 900) {
						rewardRank = 3 + ceil(maplevel / 10);
					}
					else {
						rewardRank = 2 + ceil(maplevel / 10);
					}
				}
			}
		}
		else {
			if (persent > 750)rewardRank = 4;
			else rewardRank = 5;
		}
		int Lucbonus = rand100000();
		if (Lucbonus < n.LUC / 100)rewardRank += 1;
		if (rewardRank > 5)rewardRank = 5;
		return rewardRank;
	}
	void PLAYER::decideReward(int rewardRank) {
		for (int i = 0;i < rewardCount;i++) {
			rewardStatus[i] = { 0 };
			rewardContens[i] = { 0 };
		}
		//upStatus{HP,STR,DEF,INT,DEX,LUK,};
		for (int i = 0;i < rewardCount;i++) {
			int persent = rand100();
			float increase = 0;
			if (persent < 85) {
				rewardStatus[i] = rand() % 6 + 1;//１からスタートで6個
				//ステータス上げる方の報酬
				switch (rewardRank) {
				case 1://2.0~10.0%上昇
					increase = customrand(2, 10);
					rewardContens[i] = increase;
					break;
				case 2://13.0~20.0%
					increase = customrand(13, 20);
					rewardContens[i] = increase;
					break;
				case 3://25~50%
					increase = customrand(25, 50);
					rewardContens[i] = increase;
					break;
				case 4://60~80
					increase = customrand(60, 80);
					rewardContens[i] = increase;
					break;
				case 5://85~100
					increase = customrand(85, 100);
					rewardContens[i] = increase;
					break;
				}
			}
			else {
				rewardStatus[i] = 0;
				//特殊な奴
				rewardContens[i] = 0;//0 = ドレイン効果の付与/効果量の上昇
			}
		}
		decidereward = false;
	}
	void PLAYER::drawReward(int rewardStatus[], float rewardContens[], int rewardRank) {
		if (rewardRank == 1)clear(200);
		if (rewardRank == 2)clear(51, 255, 79);
		if (rewardRank == 3)clear(86, 56, 255);
		if (rewardRank == 4)clear(134, 0, 163);
		if (rewardRank == 5)clear(255, 245, 0);
		std::string s;
		for (int i = 0;i < rewardCount;i++) {//表示
			switch (rewardStatus[i]) {
			case 1://HP(最大)
				s = "HPUP" + std::to_string((int)rewardContens[i]) + "%";
				break;
			case 2://STR
				s = "STRUP" + std::to_string((int)rewardContens[i]) + "%";
				break;
			case 3://DEF
				s = "DEFUP" + std::to_string((int)rewardContens[i]) + "%";
				break;
			case 4://INT
				s = "INTUP" + std::to_string((int)rewardContens[i]) + "%";
				break;
			case 5://DEX
				s = "DEXUP" + std::to_string((int)rewardContens[i]) + "%";
				break;
			case 6://LUC
				s = "LUCUP" + std::to_string((int)rewardContens[i]) + "%";
				break;
			case 0://special
				if(rewardContens[i]==0){ s = "HP吸収効果+10%"; }
				else s = "noreward";
				break;
			}
			float textX = (width / 2) - s.size();
			float textY = (height / 4) * (i + 1);
			fill(255, 255, 255);
			text("↑↓キーで選択", 50, height / 2 + 50);
			if (NoReroll)text("Rキーで１度だけリロール", 50, height / 2 + 100);
			text("Eキーでステータス等表示", 50, height - 50);
			if (isTrigger(KEY_R)&&NoReroll) {
				decideReward(rewardRank);
				NoReroll = false;
			}
			if (isTrigger(KEY_E)) {
				UI->setindex(1);
				game->openUI = true;
			}
			if (choiceCursor == i)fill(255, 0, 0);
			textSize(50);
			text(s.c_str(), textX, textY);
		}
	}
	void PLAYER::choiceReward(int rewardStatus[], float rewardContens[]) {
		if (isTrigger(KEY_UP)) {
			choiceCursor--;
			if (choiceCursor < 0)choiceCursor = 2;
		}
		if (isTrigger(KEY_DOWN)) {
			choiceCursor++;
			if (choiceCursor > 2)choiceCursor = 0;
		}
		if (isTrigger(KEY_ENTER)) {
			switch (rewardStatus[choiceCursor]) {
			case 1://HP
				MaxHp *= ((rewardContens[choiceCursor] / 100) + 1);
				n.HP *= ((rewardContens[choiceCursor] / 100) + 1);
				break;
			case 2://STR
				n.STR *= ((rewardContens[choiceCursor] / 100) + 1);
				break;
			case 3://DEF
				n.DEF *= ((rewardContens[choiceCursor] / 100) + 1);
				break;
			case 4://INT
				n.INT *= ((rewardContens[choiceCursor] / 100) + 1);
				break;
			case 5://DEX
				n.DEX *= ((rewardContens[choiceCursor] / 100) + 1);
				break;
			case 6://LUC
				n.LUC *= ((rewardContens[choiceCursor] / 100) + 1);
				break;
			case 0://special
				if (rewardContens[choiceCursor] == 0) { HPAbsorptionEffect += 10; }
				break;
			}
			NoReroll = true;
			game->getRewardMode = false;
		}
	}
	void PLAYER::restAreaPowerUp() {
		int Col = width / size;
		int Row = height / size + 1;
		enum STATUS { Hp, maxHp, STR, DEF, INT, DEX, LUC, COUNT };
		std::ostringstream status[COUNT];
		status[Hp] << std::fixed << std::setprecision(2) << getHp();
		status[maxHp] << std::fixed << std::setprecision(2) << getMaxHp();
		status[STR] << std::fixed << std::setprecision(2) << getSTR();
		status[DEF] << std::fixed << std::setprecision(2) << getDEF();
		status[INT] << std::fixed << std::setprecision(2) << getINT();
		status[DEX] << std::fixed << std::setprecision(2) << getDEX();
		status[LUC] << std::fixed << std::setprecision(2) << getLUC();
		std::string p = "AllocatePoint:" + std::to_string(maxAllocatePoint);
		text(p.c_str(), width - ((p.size() / 2) * size) - size, (size*2));
		for (int c = 0;c < Col;c++) {
			for (int r = 0;r < Row;r++) {
				if (c == 0 || r == 1 || c == Col - 1 || r == Row - 1) {
					fill(255);
					text("枠", c * size, r * size);
				}
			}
		}
		for (int i = 0;i < COUNT;i++) {
				std::string s;
				if (i == 1) {
					s = status[maxHp].str();
					s = "MaxHP ：" + s;

				}
				else if (i == 0)continue;
				else {
					s = status[i].str();
					if (i == 2)s = "STR：" + s;
					else if (i == 3)s = "DEF：" + s;
					else if (i == 4)s = "INT：" + s;
					else if (i == 5)s = "DEX：" + s;
					else if (i == 6)s = "LUC：" + s;
				}
				if (i == choiceCursor)fill(255, 0, 0);
				else fill(255);
				int drawX = size * 2;
				int drawY = (size * 2) + ((height / 6) - size) + (i * size);//(1080/6=180)←六等分-60←それから真ん中に +(i*size)←毎回２行ずつずらすiが行数sizeが一行の縦幅
				text(s.c_str(), drawX, drawY);
			}
		switch (index) {
		case 1:
			if (isTrigger(KEY_UP))choiceCursor--;
			if (isTrigger(KEY_DOWN))choiceCursor++;
			if (choiceCursor > COUNT - 1)choiceCursor = 1;
			if (choiceCursor < 1)choiceCursor = COUNT - 1;
			if (isPress(KEY_SHIFT) && isTrigger(KEY_ENTER)) {
				map->Cell[PCellx][PCelly].type = 0;
				game->allocate = false;
			}
			if (isTrigger(KEY_ENTER)&&game->allocate)index++;
			fill(255);
			text("ENTERでポイントを割り振るステータスを選択", size, height - (size * 3));
			text("SHIFT+ENTERで割り振りを確定し、終了", size, height - (size * 2));
			break;
		case 2:
			if (isTrigger(KEY_UP) && maxAllocatePoint > 0) {
				switch (choiceCursor) {
				case maxHp:
					MaxHp++;
					maxAllocatePoint--;
					break;
				case STR:
					n.STR++;
					maxAllocatePoint--;
					break;
				case DEF:
					n.DEF++;
					maxAllocatePoint--;
					break;
				case INT:
					n.INT++;
					maxAllocatePoint--;
					break;
				case DEX:
					n.DEX++;
					maxAllocatePoint--;
					break;
				case LUC:
					n.LUC++;
					maxAllocatePoint--;
					break;
				}
			}
			if (isTrigger(KEY_DOWN) && maxAllocatePoint < MAllocateP) {
				switch (choiceCursor) {
				case maxHp:
					if (nowStatus[maxHp] < MaxHp) {
						MaxHp--;
						maxAllocatePoint++;
					}
					break;
				case STR:
					if (nowStatus[STR] < n.STR) {
						n.STR--;
						maxAllocatePoint++;
					}
					break;
				case DEF:
					if (nowStatus[DEF] < n.DEF) {
						n.DEF--;
						maxAllocatePoint++;
					}
					break;
				case INT:
					if (nowStatus[INT] < n.INT) {
						n.INT--;
						maxAllocatePoint++;
					}
					break;
				case DEX:
					if (nowStatus[DEX] < n.DEX) {
						n.DEX--;
						maxAllocatePoint++;
					}
					break;
				case LUC:
					if (nowStatus[LUC] < n.LUC) {
						n.LUC--;
						maxAllocatePoint++;
					}
					break;
				}
			}
			if (isTrigger(KEY_ENTER))index--;
			fill(255);
			text("↑↓キーで割り振りを行う", size, height - (size * 3));
			text("ENTERで割り振りを行うステータスの選択へ", size, height - (size*2));
			break;
		}
	}
	void PLAYER::goNextLevel() {
		game->bossDefeated = false;
		getExp();
		map->update();
		game->spawnEnemy();
	}
}