#include"UserInterface.h"
#include"GAME.h"
#include"PLAYER.h"
#include<string>
#include<sstream>
#include<iomanip>
namespace GAME01
{
	UserInterface::~UserInterface() {
		game = nullptr;
		player = nullptr;
	}
	void UserInterface::init() {
		size = 60;
		Col = width / size;
		Row = height / size;
		entryNum = 4;
		choiceCursor = 1;
		index = 1;
	}
	void UserInterface::openUI() {
		clear(0);
		textSize(size);

		std::string menu[] = {
			"STATUS",
			"ITEM",
			"WEAPON",
			"EXIT",
		};
		switch (index) {
		case 1://目次
			wardCount = 0;
			//表示
			for (int c = 0;c < Col;c++) {
				for (int r = 0;r < Row;r++) {
					if (c == 0 || r == 1 || c == Col - 1 || r == Row - 1) {
						fill(255);
						text("枠", c * size, r * size);
					}
					else if (r == 2) {
						if (c == 1) {
							if (choiceCursor == c)fill(255, 0, 0);
							else fill(255);
							text(menu[c - 1].c_str(), c * size, r * size);
							wardCount += ((menu[c - 1].size() / 2) * size);
						}
						else if (c == 2) {
							if (choiceCursor == c)fill(255, 0, 0);
							else fill(255);
							text(menu[c - 1].c_str(), (c * size) + wardCount, r * size);
							wardCount += ((menu[c - 1].size() / 2) * size);
						}
						else if (c == 3) {
							if (choiceCursor == c)fill(255, 0, 0);
							else fill(255);
							text(menu[c - 1].c_str(), (c * size) + wardCount, r * size);
							wardCount += ((menu[c - 1].size() / 2) * size);
						}
						else if (c == 4) {
							if (choiceCursor == c)fill(255, 0, 0);
							else fill(255);
							text(menu[c - 1].c_str(), (c * size) + wardCount, r * size);
						}
					}
				}
			}
			text("←→キーで選択", width / 2-150, height - (size * 2));
			text("ENTERで確定", width - (size * 9), height - (size * 2));
			text("SHIFT+ENTERを押して戻る", size, height - (size * 2));
			//選択
			if (isTrigger(KEY_RIGHT)) choiceCursor++;
			if (isTrigger(KEY_LEFT))choiceCursor--;
			if (choiceCursor > entryNum)choiceCursor = 1;
			if (choiceCursor < 1)choiceCursor = entryNum;
			if (isTrigger(KEY_ENTER))index = choiceCursor + 1;
			if (isPress(KEY_SHIFT) && isTrigger(KEY_ENTER))game->openUI = false;
			break;
		case 2://STATUS
		{
			enum STATUS { Hp, MaxHp, STR, DEF, INT, DEX, LUC, COUNT };
			std::ostringstream status[COUNT];
			status[Hp] << std::fixed << std::setprecision(2) << player->getHp();
			status[MaxHp] << std::fixed << std::setprecision(2) << player->getMaxHp();
			status[STR] << std::fixed << std::setprecision(2) << player->getSTR();
			status[DEF] << std::fixed << std::setprecision(2) << player->getDEF();
			status[INT] << std::fixed << std::setprecision(2) << player->getINT();
			status[DEX] << std::fixed << std::setprecision(2) << player->getDEX();
			status[LUC] << std::fixed << std::setprecision(2) << player->getLUC();
			for (int c = 0;c < Col;c++) {
				for (int r = 0;r < Row;r++) {
					if (c == 0 || r == 1 || c == Col - 1 || r == Row - 1) {
						fill(255);
						text("枠", c * size, r * size);
					}
					if (r == 2 && c == 1)text(menu[index - 2].c_str(), c * size, r * size);
				}
			}
			for (int i = 0;i < COUNT;i++) {
				std::string s;
				if (i < 2) {
					s = status[Hp].str() + "/" + status[MaxHp].str();
					s = "HP ：" + s;

				}
				else {
					s = status[i].str();
					if (i == 2)s = "STR：" + s;
					else if (i == 3)s = "DEF：" + s;
					else if (i == 4)s = "INT：" + s;
					else if (i == 5)s = "DEX：" + s;
					else if (i == 6)s = "LUC：" + s;
				}
				int drawX = size * 2;
				int drawY = (size * 2) + ((height / 6) - size) + (i * size);//(1080/6=180)←六等分-60←それから真ん中に +(i*size)←毎回２行ずつずらすiが行数sizeが一行の縦幅
				if(i!=0)text(s.c_str(), drawX, drawY);
			}
			if (player->getHPAbsorption() != 0) {
				std::string s;
				s = "HP吸収：" + std::to_string(player->getHPAbsorption()) + "%";
				text(s.c_str(), width / 2, (height / 6)-size);
			}
			text("SHIFT+ENTERを押して戻る", size, height - (size * 2));
			if (isPress(KEY_SHIFT) && isTrigger(KEY_ENTER))index = 1;
			break;
		}
		case 3://ITEM
			for (int c = 0;c < Col;c++) {
				for (int r = 0;r < Row;r++) {
					if (c == 0 || r == 1 || c == Col - 1 || r == Row - 1) {
						fill(255);
						text("枠", c * size, r * size);
					}
					if (r == 2 && c == 1)text(menu[index - 2].c_str(), c * size, r * size);
				}
			}
			text("　未　実　装　", (width / 2) - 180, height / 2);
			text("SHIFT+ENTERを押して戻る", size, height - (size * 2));
			if (isPress(KEY_SHIFT) && isTrigger(KEY_ENTER))index = 1;
			break;
		case 4://WEAPON
			for (int c = 0;c < Col;c++) {
				for (int r = 0;r < Row;r++) {
					if (c == 0 || r == 1 || c == Col - 1 || r == Row - 1) {
						fill(255);
						text("枠", c * size, r * size);
					}
					if (r == 2 && c == 1)text(menu[index - 2].c_str(), c * size, r * size);
				}
			}
			text("　未　実　装　", (width / 2) - 180, height / 2);
			text("SHIFT+ENTERを押して戻る", size, height - (size * 2));
			if (isPress(KEY_SHIFT) && isTrigger(KEY_ENTER))index = 1;
			break;
		case 5://EXIT
			for (int c = 0;c < Col;c++) {
				for (int r = 0;r < Row;r++) {
					if (c == 0 || r == 1 || c == Col - 1 || r == Row - 1) {
						fill(255);
						text("枠", c * size, r * size);
					}
					if (r == 2 && c == 1)text(menu[index - 2].c_str(), c * size, r * size);
				}
			}
			text("Tを押してタイトルに戻る", ((width - size) / 2)-(size*5), (height / 2));
			text("SHIFT+ENTERを押して戻る", size, height - (size*2));
			if (isTrigger(KEY_T)) {
				game->openUI = false;
				game->setState(0); 
			}
			if (isPress(KEY_SHIFT) && isTrigger(KEY_ENTER))index = 1;
			break;
		}
	}
}