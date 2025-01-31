#include "../../libOne/inc/libOne.h"
#include "../MAIN/MAIN.h"
#include "GAME02.h"
#include <vector>
#include <algorithm>
#include <random>
namespace GAME02
{
	int GAME::create()
	{
		snd[0] = loadSound("..\\MAIN\\assets\\game02\\click.wav");
		snd[1] = loadSound("..\\MAIN\\assets\\game02\\GOD.wav");
		snd[2] = loadSound("..\\MAIN\\assets\\game02\\puzzleBGM.wav");

		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				square[i][j].w = 100.0f;
				square[i][j].h = 100.0f;
				square[i][j].px = (width / 2 - square[i][j].w * 4) - square[i][j].w / 2 + square[i][j].w * j;
				square[i][j].py = (height / 2 - square[i][j].h * 4) - square[i][j].h / 2 + square[i][j].h * i;

				square[i][j].ansnum = 0;

				square[i][j].emptyFlag = false;
				square[i][j].ansNumFlag = true;
				square[i][j].identicalNumFlag = false;
				square[i][j].clickFlag = false;
				for (int x = 0; x < 3; x++) {
					for (int y = 0; y < 3; y++) {
						square[i][j].candidateNum[x][y] = false;
					}
				}
			}
		}

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				frame[i][j].w = 300.0f;
				frame[i][j].h = 300.0f;
				frame[i][j].px = (width / 2 - frame[i][j].w) + frame[i][j].w * j - frame[i][j].w / 2;
				frame[i][j].py = (height / 2 - frame[i][j].h) + frame[i][j].h * i - frame[i][j].h / 2;
			}
		}

		int num = 1;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				numButton[i][j].w = 100.0f;
				numButton[i][j].h = 100.0f;
				numButton[i][j].px = (width / 2 - numButton[i][j].w) + numButton[i][j].w * j - numButton[i][j].w / 2 + 650.0f;
				numButton[i][j].py = (height / 2 - numButton[i][j].h) + numButton[i][j].h * i - numButton[i][j].h / 2 - 300.0f + 150.0f;
				numButton[i][j].num = num;


				candidateNumButton[i][j].w = 100.0f;
				candidateNumButton[i][j].h = 100.0f;
				candidateNumButton[i][j].px = (width / 2 - candidateNumButton[i][j].w) + candidateNumButton[i][j].w * j - candidateNumButton[i][j].w / 2 + 650.0f;
				candidateNumButton[i][j].py = (height / 2 - candidateNumButton[i][j].h) + candidateNumButton[i][j].h * i - candidateNumButton[i][j].h / 2 + 150.0f;
				candidateNumButton[i][j].num = num;

				num++;
			}
		}

		resetButton.w = 400.0f;
		resetButton.h = 200.0f;
		resetButton.px = (width / 2 - resetButton.w) - 500.0f;
		resetButton.py = (height / 2 - resetButton.h)- 100.0f;

		titleReturnButton.w = 400.0f;
		titleReturnButton.h = 200.0f;
		titleReturnButton.px = (width / 2 - titleReturnButton.w) - 500.0f;
		titleReturnButton.py = (height / 2 - titleReturnButton.h) - 100.0f + titleReturnButton.h * 2;

		for (int i = 0; i < 3; i++) {
			titleButton[i].w = 400.0f;
			titleButton[i].h = 200.0f;
			titleButton[i].px = (width / 2 - titleButton[i].w) - titleButton[i].w + i * (titleButton[i].w * 1.5f);
			titleButton[i].py = (height / 2 - titleButton[i].h) + 300.0f;
		}

		levelDifficulty = 0;
		clearFlag = false;
		colTime = 0;
		once = true;

		return 0;
	}

	void GAME::destroy()
	{

	}

	bool GAME::numCheck(int x, int y, int num) {
		for (int i = 0; i < 9; i++) {
			if (x != i && num == square[i][y].num)	return false;
		}

		for (int i = 0; i < 9; i++) {
			if (y != i && num == square[x][i].num)	return false;
		}

		int startX = x / 3 * 3;
		int startY = y / 3 * 3;
		for (int i = startX; i < startX + 3; i++) {
			for (int j = startY; j < startY + 3; j++) {
				if (x != i && y != j && num == square[i][j].num) return false;
			}
		}

		return true;
	}

	bool GAME::ansNumCheck(int x, int y, int num) {
		for (int i = 0; i < 9; i++) {
			if (x != i && num == square[i][y].ansnum)	return false;
		}

		for (int i = 0; i < 9; i++) {
			if (y != i && num == square[x][i].ansnum)	return false;
		}

		int startX = x / 3 * 3;
		int startY = y / 3 * 3;
		for (int i = startX; i < startX + 3; i++) {
			for (int j = startY; j < startY + 3; j++) {
				if (x != i && y != j && num == square[i][j].ansnum) return false;
			}
		}

		return true;
	}

	bool GAME::setnum()
	{
		for (int x = 0; x < 9; x++) {
			for (int y = 0; y < 9; y++) {
				if (square[x][y].ansnum == 0) {
					std::vector<int> nums = { 1,2,3,4,5,6,7,8,9 };
					std::random_device rd;
					std::mt19937 g(rd());
					shuffle(nums.begin(), nums.end(), g);
					for (int num : nums) {
						if (ansNumCheck(x, y, num)) {
							square[x][y].ansnum = num;
							square[x][y].ansNumFlag = true;
							if (setnum()) {
								return true;
							}
							square[x][y].ansnum = 0;
							square[x][y].ansNumFlag = false;
						}
					}
					return false;
				}
			}
		}
		return true;
	}

	bool GAME::solveQ(int& solutionCount) {
		for (int x = 0; x < 9; x++) {
			for (int y = 0; y < 9; y++) {
				if (square[x][y].num == 0) {
					for (int num = 1; num < 10; num++) {
						if (numCheck(x, y, num)) {
							square[x][y].num = num;
							if (solveQ(solutionCount)) {
								return true;
							}
							square[x][y].num = 0;
						}
					}
					return false;
				}
			}
		}
		solutionCount++;
		return false;
	}

	void GAME::createQ() {
		for (int x = 0; x < 9; x++) {
			for (int y = 0; y < 9; y++) {
				square[x][y].num = square[x][y].ansnum;
				if (square[x][y].num != 0) {
					square[x][y].emptyFlag = false;
					square[x][y].ansNumFlag = true;
				}
				else {
					square[x][y].emptyFlag = true;
					square[x][y].ansNumFlag = false;
				}
			}
		}

		std::vector<int> nums;
		for (int i = 0; i < 81; i++) {
			nums.emplace_back(i);
		}
		std::random_device rd;
		std::mt19937 g(rd());
		shuffle(nums.begin(), nums.end(), g);
		auto it = nums.begin();
		for (int i = 0; i < deleteNum; i++) {
			int y = *it / 9;
			int x = *it % 9;
			square[x][y].num = 0;
			square[x][y].emptyFlag = true;
			square[x][y].ansNumFlag = false;
			it++;
		}
	}

	bool GAME::clearCheck() {
		int correctNum = 0;
		for (int x = 0; x < 9; x++) {
			for (int y = 0; y < 9; y++) {
				if (square[x][y].ansnum == square[x][y].num && square[x][y].emptyFlag == false) {
					correctNum++;
				}
				else correctNum = 0;
			}
		}
		if (correctNum >= 81) {
			return true;
		}
		else return false;
	}

	void GAME::numcopy() {
		for (int x = 0; x < 9; x++) {
			for (int y = 0; y < 9; y++) {
				if (square[x][y].clickFlag && square[x][y].ansNumFlag == false) {
					for (int i = 0; i < 3; i++) {
						for (int j = 0; j < 3; j++) {
							if (numButton[i][j].selectFlag) {
								if (numButton[i][j].num == square[x][y].num) { square[x][y].num = 0; square[x][y].emptyFlag = true; }
								else { square[x][y].num = numButton[i][j].num; square[x][y].emptyFlag = false; }
							}
						}
					}
				}
			}
		}
	}

	void GAME::playDraw() {
		clear(128);
		strokeWeight(5);
		for (int x = 0; x < 9; x++) {
			for (int y = 0; y < 9; y++) {
				if (square[x][y].ansNumFlag == false)fill(255);
				else fill(224);

				if (square[x][y].clickFlag == true && square[x][y].num != 0) {
					for (int i = 0; i < 9; i++) {
						for (int j = 0; j < 9; j++) {
							if (square[x][y].num == square[i][j].num || (square[x][y].num == square[i][j].ansnum && square[i][j].ansNumFlag == true)) {
								square[i][j].identicalNumFlag = true;
							}
						}
					}
				}
				if (square[x][y].identicalNumFlag)fill(255, 255, 130);
				if (square[x][y].clickFlag)fill(255, 30, 30);
				rect(square[x][y].px, square[x][y].py, square[x][y].w, square[x][y].h);
				fill(0);
				if (square[x][y].num != 0)text((let)+square[x][y].num, square[x][y].px + 38, square[x][y].py + 78);
			}
		}


		strokeWeight(10);
		fill(255, 255, 255, 0);
		for (int x = 0; x < 3; x++) {
			for (int y = 0; y < 3; y++) {
				rect(frame[x][y].px, frame[x][y].py, frame[x][y].w, frame[x][y].h);
			}
		}

		if (!clearFlag) {
			for (int x = 0; x < 3; x++) {
				for (int y = 0; y < 3; y++) {
					fill(255);
					rect(numButton[x][y].px, numButton[x][y].py, numButton[x][y].w, numButton[x][y].h);
					rect(candidateNumButton[x][y].px, candidateNumButton[x][y].py, candidateNumButton[x][y].w, candidateNumButton[x][y].h);

				}
			}


			fill(0);

			for (int x = 0; x < 3; x++) {
				for (int y = 0; y < 3; y++) {
					text((let)+numButton[x][y].num, numButton[x][y].px + 38, numButton[x][y].py + 78);
				}
			}



			textSize(30.0f);
			for (int x = 0; x < 3; x++) {
				for (int y = 0; y < 3; y++) {
					text((let)+candidateNumButton[x][y].num, candidateNumButton[x][y].px + 15 + (y * 25), candidateNumButton[x][y].py + 40 + (x * 25));
					for (int i = 0; i < 9; i++) {
						for (int j = 0; j < 9; j++) {
							if (square[i][j].emptyFlag && square[i][j].candidateNum[x][y] != 0)
								text((let)+square[i][j].candidateNum[x][y], square[i][j].px + 15 + (y * 25), square[i][j].py + 40 + (x * 25));
						}
					}
				}
			}
			textSize(50.0f);

			fill(255);
			strokeWeight(10);
			rect(resetButton.px, resetButton.py, resetButton.w, resetButton.h);
			rect(titleReturnButton.px, titleReturnButton.py, titleReturnButton.w, titleReturnButton.h);
			fill(0);
			text("盤面リセット", resetButton.px + 50.0f, resetButton.py + 125.0f);
			text("タイトルに戻る", titleReturnButton.px + 25.0f, titleReturnButton.py + 125.0f);
		}
	}

	void GAME::playMousecol() {
		if (colTime < 10) {
			colTime++;
		}
		//盤面の判定
		for (int x = 0; x < 9; x++) {
			for (int y = 0; y < 9; y++) {
				if (mouseX > square[x][y].px && mouseX < square[x][y].px + square[x][y].w &&
					mouseY > square[x][y].py && mouseY < square[x][y].py + square[x][y].h) {
					if (isTrigger(MOUSE_LBUTTON) && colTime >= 10) {
						playSound(snd[0]);
						for (int i = 0; i < 9; i++) {
							for (int j = 0; j < 9; j++) {
								square[i][j].clickFlag = false;
								square[i][j].identicalNumFlag = false;
							}
						}
						for (int i = 0; i < 3; i++) {
							for (int j = 0; j < 3; j++) {
								numButton[i][j].selectFlag = false;
							}
						}
						square[x][y].clickFlag = true;
					}
				}
			}
		}
		//数字選択の判定
		for (int x = 0; x < 3; x++) {
			for (int y = 0; y < 3; y++) {
				if (mouseX > numButton[x][y].px && mouseX < numButton[x][y].px + numButton[x][y].w &&
					mouseY > numButton[x][y].py && mouseY < numButton[x][y].py + numButton[x][y].h) {
					if (isTrigger(MOUSE_LBUTTON)) {
						playSound(snd[0]);
						for (int i = 0; i < 9; i++) {
							for (int j = 0; j < 9; j++) {
								square[i][j].identicalNumFlag = false;
							}
						}
						for (int i = 0; i < 3; i++) {
							for (int j = 0; j < 3; j++) {
								numButton[i][j].selectFlag = false;
							}
						}
						numButton[x][y].selectFlag = true;
						numcopy();
					}
				}
			}
		}
		//候補数字選択の判定
		for (int x = 0; x < 3; x++) {
			for (int y = 0; y < 3; y++) {
				if (mouseX > candidateNumButton[x][y].px && mouseX < candidateNumButton[x][y].px + candidateNumButton[x][y].w &&
					mouseY > candidateNumButton[x][y].py && mouseY < candidateNumButton[x][y].py + candidateNumButton[x][y].h) {
					if (isTrigger(MOUSE_LBUTTON)) {
						
						for (int i = 0; i < 9; i++) {
							for (int j = 0; j < 9; j++) {
								if (square[i][j].clickFlag && square[i][j].emptyFlag) {
									if (square[i][j].candidateNum[x][y] != candidateNumButton[x][y].num) {
										playSound(snd[0]);
										square[i][j].candidateNum[x][y] = candidateNumButton[x][y].num;
									}
									else { playSound(snd[0]); square[i][j].candidateNum[x][y] = 0; }
								}
							}
						}
					}
				}
			}
		}

		//その他の判定
		for (int x = 0; x < 9; x++) {
			for (int y = 0; y < 9; y++) {
				if (mouseX > resetButton.px && mouseX < resetButton.px + resetButton.w &&
					mouseY > resetButton.py && mouseY < resetButton.py + resetButton.h) {
					if (isTrigger(MOUSE_LBUTTON)) {
						playSound(snd[0]);
						if (!square[x][y].ansNumFlag) {
							square[x][y].num = 0;
							for (int i = 0; i < 3; i++) {
								for (int j = 0; j < 3; j++) {
									square[x][y].candidateNum[i][j] = 0;
								}
							}
						}
						square[x][y].clickFlag = false;
						square[x][y].identicalNumFlag = false;
					}
				}
			}
		}
		
		if (mouseX > titleReturnButton.px && mouseX < titleReturnButton.px + titleReturnButton.w &&
			mouseY > titleReturnButton.py && mouseY < titleReturnButton.py + titleReturnButton.h) {
			if (isTrigger(MOUSE_LBUTTON) && colTime >= 10) {
				playSound(snd[0]);
				State = TITLE;
			}
		}
	}

	void GAME::titleDraw(){
		fill(0);
		textSize(200);
		text("ナンプレ", width / 2 - 400, height / 2 - 100);
		fill(255);
		strokeWeight(10);
		for (int i = 0; i < 3; i++) {
			rect(titleButton[i].px, titleButton[i].py, titleButton[i].w, titleButton[i].h);
		}
		fill(0);
		textSize(50);
		for (int i = 0; i < 3; i++) {
			if (i == 0) {
				text("初級", titleButton[i].px + 150.0f, titleButton[i].py + 100.0f);
			}
			else if (i == 1) {
				text("中級", titleButton[i].px + 150.0f, titleButton[i].py + 100.0f);
			}
			else {
				text("上級", titleButton[i].px + 150.0f, titleButton[i].py + 100.0f);
			}
			text("空白マスの数"+(let)+(20 + (i + 1) * 10), titleButton[i].px + 25.0f, titleButton[i].py + 150.0f);
		}
	}

	bool GAME::titleMousecol() {
		for (int i = 0; i < 3; i++) {
			if (mouseX > titleButton[i].px && mouseX < titleButton[i].px + titleButton[i].w &&
				mouseY > titleButton[i].py && mouseY < titleButton[i].py + titleButton[i].h) {
				if (isTrigger(MOUSE_LBUTTON)) {
					playSound(snd[0]);
					deleteNum = 20 + (i + 1) * 10;
					return true;
				}
			}
		}
		return false;
	}

	void GAME::title() {
		deleteNum = 0;
		titleDraw();
		if (titleMousecol()) {
			create();
			State = PLAY;
		}
	}

	void GAME::play() {
		
		while(once){ 
			setnum();
			createQ();
			solveQ(SolutionCount);
			if (SolutionCount == 1)once = false;
			else SolutionCount = 0;
		}
		
		playDraw();
		playMousecol();
		//重解の数の表示
		//text((let)+SolutionCount, 0, 880);
		if (clearCheck()) { State = CLEAR; }
		//デバッグ用
		//if (isTrigger(KEY_A)) { State = CLEAR; }
	}

	void GAME::gameclear() {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				square[i][j].emptyFlag = false;
				square[i][j].ansNumFlag = false;
				square[i][j].identicalNumFlag = false;
				square[i][j].clickFlag = false;
				for (int x = 0; x < 3; x++) {
					for (int y = 0; y < 3; y++) {
						square[i][j].candidateNum[x][y] = false;
					}
				}
			}
		}
		playDraw();
		fill(0);
		textSize(300);
		text("ク", width / 2 - 850.0f, height - 700.0f);
		text("リ", width / 2 - 850.0f, height - 400.0f);
		text("ア", width / 2 - 850.0f, height - 100.0f);
		clearFlag = true;
		//GOD
		//if (isPress(KEY_G) && isPress(KEY_O) && isTrigger(KEY_D) ||
		//	isPress(KEY_G) && isTrigger(KEY_O) && isPress(KEY_D) ||
		//	isTrigger(KEY_G) && isPress(KEY_O) && isPress(KEY_D))playSound(snd[1]);
		if (isTrigger(KEY_SPACE)) { State = TITLE; }
	}

	void GAME::proc()
	{
		static bool bgmFlag = true;
			if (bgmFlag) {
				playLoopSound(snd[2]);
				bgmFlag = false;
			}
		
		clear(128);
		textSize(50);
		fill(255, 255, 0);
		textSize(50);
		fill(255);

		if (State == TITLE) { title(); }
		if (State == PLAY) { play(); }
		if (State == CLEAR) { gameclear(); }
		fill(0);
		textSize(50);

		if (State != CLEAR)text("ENTERキーでメニューに戻る", 0, 1080);
		else text("ENTERキーでメニューに戻る　SPACEキーでタイトルに戻る", 0, 1080);
		if (isTrigger(KEY_ENTER)) {
			main()->backToMenu();
		}
	}
}
