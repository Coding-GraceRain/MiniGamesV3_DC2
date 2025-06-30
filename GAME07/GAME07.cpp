#include "../../libOne/inc/libOne.h"
#include "../MAIN/MAIN.h"
#include "GAME07.h"
#include <time.h> 
namespace GAME07   
{				   
	int GAME::create()
	{
		State = TITLE;
		backImg = loadImage("..\\main\\assets\\game07\\back.png");
		dice1Img = loadImage("..\\main\\assets\\game07\\dice1.png");
		dice2Img = loadImage("..\\main\\assets\\game07\\dice2.png");
		dice3Img = loadImage("..\\main\\assets\\game07\\dice3.png");
		dice4Img = loadImage("..\\main\\assets\\game07\\dice4.png");
		dice5Img = loadImage("..\\main\\assets\\game07\\dice5.png");
		dice6Img = loadImage("..\\main\\assets\\game07\\dice6.png");
		oyaImg = loadImage("..\\main\\assets\\game07\\oya.png");
		yakuImg= loadImage("..\\main\\assets\\game07\\Yaku.png");
		srand(time(NULL));
		return 0;  
	}

	void GAME::destroy()
	{

	}

	void GAME::proc()
	{
		if (State == TITLE)Title();
		else if (State == YAKU)Yaku();
		else if (State == INIT)Init();
		else if (State == OYA)Oya();
		else if (State == PLAY)Play();
		else if (State == WIN)Win();
		else if (State == LOSE)Lose();
		else if (State == DRAW)Draw();
	}
	void GAME::Title() {
		rectMode(CORNER);
		clear();
		image(backImg, 150, 0);
		fill(0);
		textSize(250);
		text("チンチロ", 450, 400);
		fill(0);
		textSize(100);
		text("SPACEキー:プレイ", 500, 600);
		text("Rキー:役の一覧", 500, 700);

		if (isTrigger(KEY_SPACE)) {
			State = INIT;
		}
		if (isTrigger(KEY_R)) {
			State = YAKU;
		}
		fill(255, 0, 0);
		textSize(80);
		text("Enterでメニューに戻る", 150, height);
		if (isTrigger(KEY_ENTER)) {
			main()->backToMenu();
		}
	}
	void GAME::Yaku() {
		rectMode(CORNER);
		clear();
		image(backImg, 150, 0);
		image(yakuImg, 500, 0,0,0.8f);
		fill(0);
		textSize(80);
		text("Enterでタイトルに戻る", 150, height);
		if (isTrigger(KEY_ENTER)) {
			State = TITLE;
		}
	}
	void GAME::Init() {
		for (int j = 0; j < 3; j++) {
			oyaDice[j] = 0;
		}
		for (int j = 0; j < 3; j++) {
			playerDice[j] = 0;
		}
		oyaRolled = false;
		playerRolled = false;
		oyaYaku = 0;
		playerYaku = 0;
		oyaPair = 0;
		playerPair = 0;
		oyaZorome = 0;
		playerZorome = 0;
		ohas1 = false;
		ohas2 = false;
		ohas3 = false;
		ohas4 = false;
		ohas5 = false;
		ohas6 = false;
		phas1 = false;
		phas2 = false;
		phas3 = false;
		phas4 = false;
		phas5 = false;
		phas6 = false;

		State = OYA;
	}
	void GAME::Oya() {
		rectMode(CORNER);
		clear();
		image(backImg, 150, 0);
		rectMode(CENTER);
		image(oyaImg, Width / 2, Height / 2);
		rectMode(CENTER);
		fill(0);
		text("親の手番",150 , 100);
		textSize(100);
		text("サイコロを振る:R",500, Height);
		if (!oyaRolled && isTrigger(KEY_R)) {
			oyaDice[0] = rand() % 6 + 1;
			oyaDice[1] = rand() % 6 + 1;
			oyaDice[2] = rand() % 6 + 1;

			oyaRolled = true; 
		}

		if (oyaRolled) {
			for (int i = 0; i < 3; i++) {
				px = 700 + 250 * i;
				switch (oyaDice[i]) {
				case 1: image(dice1Img, px, py, 0, 0.2f); break;
				case 2: image(dice2Img, px, py, 0, 0.2f); break;
				case 3: image(dice3Img, px, py, 0, 0.2f); break;
				case 4: image(dice4Img, px, py, 0, 0.2f); break;
				case 5: image(dice5Img, px, py, 0, 0.2f); break;
				case 6: image(dice6Img, px, py, 0, 0.2f); break;
				}
			}
			for (int h = 0; h < 3; h++) {
				if (oyaDice[h] == 1)ohas1 = true;
				if (oyaDice[h] == 2)ohas2 = true;
				if (oyaDice[h] == 3)ohas3 = true;
			}
			for (int s = 0; s < 3; s++) {
				if (oyaDice[s] == 4)ohas4 = true;
				if (oyaDice[s] == 5)ohas5 = true;
				if (oyaDice[s] == 6)ohas6 = true;
			}
			if (ohas1&&ohas2&&ohas3) {
				fill(0, 0, 255);
				text("ヒフミ！",700,400);
				oyaYaku = 2;
			}
			else if (ohas4&&ohas5&&ohas6) {
				fill(255, 255, 0);
				text("シゴロ！", 700, 400);
				oyaYaku = 1;
			}
			else if (oyaDice[0] == oyaDice[1] && oyaDice[1] == oyaDice[2]) {
				if (oyaDice[0] == 1) {
					fill(255, 0, 0);
					text("ピンゾロ！", 700, 400);
					oyaYaku = 1;
				}
				else {
					fill(255, 255, 0);
					text("ゾロ目！", 700, 400);
					oyaYaku = 3;
					oyaZorome = oyaDice[0];
				}
			}
			else if (oyaDice[0] == oyaDice[1] || oyaDice[1] == oyaDice[2] || oyaDice[0] == oyaDice[2]) {
				fill(0);
				text("1ペア！", 700, 400);
				oyaYaku = 4;
				if (oyaDice[0] == oyaDice[1] && oyaDice[0] != oyaDice[2]) {
					oyaPair = oyaDice[2];
				}
				else if (oyaDice[0] == oyaDice[2] && oyaDice[0] != oyaDice[1]) {
					oyaPair = oyaDice[1];
				}
				else if (oyaDice[1] == oyaDice[2] && oyaDice[1] != oyaDice[0]) {
					oyaPair = oyaDice[0];
				}
			}
			else {
				fill(0, 0, 255);
				text("役なし...", 700, 400);
				oyaYaku = 2;
			}
			fill(0);
			text("Enterで次へ", 600, 100);
			if (isTrigger(KEY_ENTER)) {
				if (oyaYaku == 1) {
					State = LOSE;
				}
				else if (oyaYaku == 2) {
					State = WIN;
				}
				else {
					State = PLAY;
				}
				
				return;
			}
		}

		
	}
	void GAME::Play() {
		rectMode(CORNER);
		clear();
		image(backImg, 150, 0);
		fill(0);
		text("自分の手番", 150, 100);
		textSize(100);
		text("サイコロを振る:R", 500, Height);
		if (!playerRolled && isTrigger(KEY_R)) {
			playerDice[0] = rand() % 6 + 1;
			playerDice[1] = rand() % 6 + 1;
			playerDice[2] = rand() % 6 + 1;
			
			playerRolled = true; 
		}
		rectMode(CENTER);
		if (playerRolled) {
			for (int i = 0; i < 3; i++) {
				px = 700 + 250 * i;
				switch (playerDice[i]) {
				case 1: image(dice1Img, px, py, 0, 0.2f); break;
				case 2: image(dice2Img, px, py, 0, 0.2f); break;
				case 3: image(dice3Img, px, py, 0, 0.2f); break;
				case 4: image(dice4Img, px, py, 0, 0.2f); break;
				case 5: image(dice5Img, px, py, 0, 0.2f); break;
				case 6: image(dice6Img, px, py, 0, 0.2f); break;
				}
			}
			for (int h = 0; h < 3; h++) {
				if (playerDice[h] == 1)phas1 = true;
				if (playerDice[h] == 2)phas2 = true;
				if (playerDice[h] == 3)phas3 = true;
			}
			for (int s = 0; s < 3; s++) {
				if (playerDice[s] == 4)phas4 = true;
				if (playerDice[s] == 5)phas5 = true;
				if (playerDice[s] == 6)phas6 = true;
			}
			if (phas1&&phas2&&phas3) {
				fill(0, 0, 255);
				text("ヒフミ！", 700, 400);
				playerYaku = 2;
			}
			else if (phas4&&phas5&&phas6) {
				fill(255, 255, 0);
				text("シゴロ！", 700, 400);
				playerYaku = 1;
			}
			else if (playerDice[0] == playerDice[1] && playerDice[1] == playerDice[2]) {
				if (playerDice[0] == 1) {
					fill(255, 0, 0);
					text("ピンゾロ！", 700, 400);
					playerYaku = 1;
				}
				else {
					fill(255, 255, 0);
					text("ゾロ目！", 700, 400);
					playerZorome = playerDice[0];
					playerYaku = 3;
				}
			}
			else if (playerDice[0] == playerDice[1] || playerDice[1] == playerDice[2] || playerDice[0] == playerDice[2]) {
				fill(0);
				text("1ペア！", 700, 400);
				playerYaku = 4;
				if (playerDice[0] == playerDice[1] && playerDice[0] != playerDice[2]) {
					playerPair = playerDice[2];
				}
				else if (playerDice[0] == playerDice[2] && playerDice[0] != playerDice[1]) {
					playerPair = playerDice[1];
				}
				else if (playerDice[1] == playerDice[2] && playerDice[1] != playerDice[0]) {
					playerPair = playerDice[0];
				}
			}
			else {
				fill(0, 0, 255);
				text("役なし...", 700, 400);
				playerYaku = 2;
			}
			fill(0);
			text("Enterで次へ", 700, 100);
			if (isTrigger(KEY_ENTER)) {
				if (playerYaku == 1) {
					State = WIN;
				}
				else if (playerYaku == 2) {
					State = LOSE;
				}
				else if (playerYaku == 3) {
					if (oyaYaku == 3) {
						if (oyaZorome > playerZorome) {
							State = LOSE;
						}
						else if (oyaZorome < playerZorome) {
							State = WIN;
						}
						else if (oyaZorome == playerZorome) {
							State = DRAW;
						}
					}
					else {
						State = WIN;
					}
				}
				else if (playerYaku == 4) {
					if (oyaYaku == 4) {
						if (oyaPair > playerPair) {
							State = LOSE;
						}
						else if (oyaPair < playerPair) {
							State = WIN;
						}
						else if (oyaPair == playerPair) {
							State = DRAW;
						}
					}
					else if(oyaYaku==3){
						State = LOSE;
					}
					else {
						State = WIN;
					}
				}
				return;
			}
		}

	}
	void GAME::Win() {
		rectMode(CORNER);
		clear();
		image(backImg, 150, 0);
		fill(255, 0, 0);
		textSize(500);
		text("勝ち！", 300, 500);
		fill(0);
		textSize(80);
		text("Enterでタイトルに戻る", 150, height);
		if (isTrigger(KEY_ENTER)) {
			State = TITLE;
		}
		textSize(100);
		text("SPACE:もう一勝負", 500, 800);
		if (isTrigger(KEY_SPACE)) {
			State = INIT;
		}
	}
	void GAME::Lose() {
		rectMode(CORNER);
		clear();
		image(backImg, 150, 0);
		fill(0,0,255);
		textSize(500);
		text("負け！", 300, 500);
		fill(0);
		textSize(80);
		text("Enterでタイトルに戻る", 150, height);
		if (isTrigger(KEY_ENTER)) {
			State = TITLE;
		}
		textSize(100);
		text("SPACE:もう一勝負", 500, 800);
		if (isTrigger(KEY_SPACE)) {
			State = INIT;
		}
	}
	void GAME::Draw() {
		rectMode(CORNER);
		clear();
		image(backImg, 150, 0);
		fill(0, 255, 255);
		textSize(400);
		text("引き分け！", 200, 500);
		fill(0);
		textSize(80);
		text("Enterでタイトルに戻る", 150, height);
		if (isTrigger(KEY_ENTER)) {
			State = TITLE;
		}
		textSize(100);
		text("SPACE:もう一勝負", 500, 800);
		if (isTrigger(KEY_SPACE)) {
			State = INIT;
		}
	}
}
