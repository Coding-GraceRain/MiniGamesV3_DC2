#include "../../libOne/inc/libOne.h"
#include "../MAIN/MAIN.h"
#include "GAME02.h"
#include <time.h>
extern bool EscapeKeyValid;
namespace GAME02{
	const int cardall = 14;
	int cardimg[cardall];
	int a;
	//ゲーム中ステータス
	int gamest = 0;
	int maingame = 0;
	int BGM = 0;
	//ディーラー
	int GDE = 0;
	int randDE1 = 0;
	int randDE2 = 0;
	int randDE3 = 0;
	int randDE4 = 0;
	int randDE5 = 0;
	//自分
	int GME = 0;
	int randME1 = 0;
	int randME2 = 0;
	int randME3 = 0;
	int randME4 = 0;
	int randME5 = 0;
	//カウント
	int Hitcount = 0;
	int Scount = 0;
	int re = 0;
	//音楽
	int Sound = 0;

	int GAME::create() {
		BGM = 0;
		/*for (int i = 0; i < cardall; i++) {
			//char filename[64];
			//sprintf_s(filename, "../MAIN/assets/game02/%d.png", i + 1);
		}*/
		//カードの画像ロード
		cardimg[0] = loadImage("..\\MAIN\\assets\\game02\\0.png");
		cardimg[1] = loadImage("..\\MAIN\\assets\\game02\\1.png");
		cardimg[2] = loadImage("..\\MAIN\\assets\\game02\\2.png");
		cardimg[3] = loadImage("..\\MAIN\\assets\\game02\\3.png");
		cardimg[4] = loadImage("..\\MAIN\\assets\\game02\\4.png");
		cardimg[5] = loadImage("..\\MAIN\\assets\\game02\\5.png");
		cardimg[6] = loadImage("..\\MAIN\\assets\\game02\\6.png");
		cardimg[7] = loadImage("..\\MAIN\\assets\\game02\\7.png");
		cardimg[8] = loadImage("..\\MAIN\\assets\\game02\\8.png");
		cardimg[9] = loadImage("..\\MAIN\\assets\\game02\\9.png");
		cardimg[10] = loadImage("..\\MAIN\\assets\\game02\\10.png");
		cardimg[11] = loadImage("..\\MAIN\\assets\\game02\\11.png");
		cardimg[12] = loadImage("..\\MAIN\\assets\\game02\\12.png");
		cardimg[13] = loadImage("..\\MAIN\\assets\\game02\\13.png");
		//音楽をロード
		Sound = loadSound("..\\MAIN\\assets\\game02\\BGM.wav");
		//メインループ側でのESCキーでの終了判定を無効化する
		EscapeKeyValid = false;
		//ここにはゲーム開始時に1回だけ行うものを記述する
		textSize(200);
		return 0;
	}
	void GAME::destroy(){
		//メインループ側でのESCキーでの終了判定を有効化する
		EscapeKeyValid = true;
		//ここにはゲーム終了時に1回だけ行うものを記述する
		stopSound(Sound);
		gamest = 0;
		reset();
	}
	void GAME::reset() {
		GDE = 0;
		GME = 0;
		Scount = 0;
		Hitcount = 0;
		randDE1 = 0;
		randDE2 = 0;
		randDE3 = 0;
		randDE4 = 0;
		randDE5 = 0;
		randME1 = 0;
		randME2 = 0;
		randME3 = 0;
		randME4 = 0;
		randME5 = 0;
		maingame = 0;
		re = 0;
	}
	void GAME::proc() {
		//BGM　ON
		if (BGM == 0) {
			playSound(Sound);//音楽再生
			BGM = 1;
		}
		if (gamest == 0) {
			//タイトル
			clear(0, 80, 0);
			textSize(150);
			text("ブラックジャック", 350, 250);
			textSize(110);
			text("スペースキーを押してスタート", 200, 900);
			text("21に近い方が勝利！", 500, 600);
			if (isTrigger(KEY_SPACE)) {//ゲームに入る
				gamest = 1;
			}
		}
		if (gamest != 0) {
			/*
			clear(0, 0, 64);
			if (isTrigger(KEY_ENTER)) {
				//手札
				/*for (int i = 0; i < 9; i++) {
					//ランダムな数を入れる
					srand(time(0));
					randDE[i] = rand() % 13;
					randME[i] = rand() % 13;
					//決められた乱数を画像呼び出しにいれる
					DEimg[i] = randDE[i];
					MEimg[i] = randME[i];
					//11以上は10に
					if (randDE[i] >= 11) {
						randDE[i] = 10;
					}
					if (randME[i] >= 11) {
						randME[i] = 10;
					}
					//内部の数値（累計）をいれる
					for (int j = i + 1; j < 9; j++) {
						GDE[j] += randDE[i];
						GME[j] += randME[i];
					}
					if (GDE[i] > 21) {
						Dcard = i;
					}
					if (GME[i] > 21) {
						Mcard = i;
					}
					for (int i = 0; i < Dcard; i++) {
						DF = i;
					}
					for (int i = 0; i < Mcard; i++) {
						MF = i;
					}
				}
			}
			*/
			srand(time(0));
			if (maingame != 100) {
				//ディーラーと自分の1、2枚目準備
				randDE1 = rand() % 10 + 1;
				GDE += randDE1;
				randDE2 = rand() % 10 + 1;
				GDE += randDE2;
				randME1 = rand() % 10 + 1;
				GME += randME1;
				randME2 = rand() % 10 + 1;
				GME += randME2;
				maingame = 100;
			}
			clear(0, 80, 0);
			//ディーラーカード準備
			image(cardimg[randDE1], 100, 50);
			image(cardimg[randDE2], 200, 50);
			image(cardimg[randDE3], 300, 50);
			image(cardimg[randDE4], 400, 50);
			image(cardimg[randDE5], 500, 50);
			//自分カード準備
			image(cardimg[randME1], 1100, 50);
			image(cardimg[randME2], 1200, 50);
			image(cardimg[randME3], 1300, 50);
			image(cardimg[randME4], 1400, 50);
			image(cardimg[randME5], 1500, 50);
			text("ディーラーの数", 100, 600);
			text(GDE, 100, 650);
			text("自分の数", 1100, 600);
			text(GME, 1100, 650);
			textSize(200);
			text("VS", 850, 400);
			if (Scount == 0) {    //勝負が決まっていない間
				textSize(50);
				text("ヒットなら方向キー上･スタンドならenterキー", 850, 1070);
				text("＊カードは5枚まで", 1475, 1000);
			}
			//ヒット
			if (isTrigger(KEY_UP)) {
				//キーを押すたびにカード表示
				if (Hitcount == 0) {
					randME3 = rand() % 10 + 1;
					GME += randME3;
				}
				if (Hitcount == 1) {
					randME4 = rand() % 10 + 1;
					GME += randME4;
				}
				if (Hitcount == 2) {
					randME5 = rand() % 10 + 1;
					GME += randME5;
				}
				Hitcount++;
			}
			//ブラックジャックなら即勝ち
			if (GME == 21) {
				Scount = 5;
				re = 1;
			}
			
			if (Scount == 0) {//勝負が決まるまでしか押せない
				if (isTrigger(KEY_ENTER)) {    //スタンド
					re = 1;
					//ディーラーのカード2枚目以降表示
					if (GDE <= 18) {
						randDE3 = rand() % 10 + 1;
						GDE += randDE3;
					}
					if (GDE <= 18) {
						randDE4 = rand() % 10 + 1;
						GDE += randDE4;
					}
					if (GDE <= 18) {
						randDE5 = rand() % 10 + 1;
						GDE += randDE5;
					}
					//勝利条件
					if (GDE > GME && GDE <= 21) {
						Scount = 3;
					}
					if (GDE < GME && GME <= 21) {
						Scount = 4;
					}
					if (GDE > 21) {
						Scount = 2;
					}
					if (GME > 21) {
						Scount = 1;
					}
					if (GDE > 21 && GME > 21) {
						Scount = 6;
					}
					if (GDE == GME) {
						Scount = 6;
					}
					if (GDE == 21 && (GME != 21 || GME > 21)) {
						Scount = 7;
					}
				}
			}
			//勝利判定
			switch (Scount) {
			case 1:
				textSize(110);
				text("バースト！", 750, 800);
				text("YOU LOSE", 750, 900);
				break;
			case 2:
				textSize(110);
				text("ディーラーがバースト！", 350, 800);
				text("YOU WIN!", 750, 900);
				break;
			case 3:
				textSize(110);
				text("YOU LOSE", 750, 900);
				break;
			case 4:
				textSize(110);
				text("YOU WIN!", 750, 900);
				break;
			case 5:
				textSize(110);
				text("ブラックジャック！！！！！", 200, 800);
				text("VICTORY!!!!", 680, 900);
				break;
			case 6:
				textSize(110);
				text("DRAW", 850, 900);
				break;
			case 7:
				textSize(110);
				text("ディーラーがブラックジャック", 200, 800);
				text("YOU LOSE...", 680, 900);
			}
			//リセット
			if (re == 1) {
				textSize(50);
				text("以降のカードが見たい場合は方向キー上", 1020, 1080);
				text("方向キー下でリスタート", 1370, 1020);
				if (isTrigger(KEY_DOWN)) {
					reset();
				}
			}
		}
		fill(255);
		textSize(50);
		text("ESCキーでメニューに戻る", 0, 1080);
		if (isTrigger(KEY_ESCAPE)) {
			main()->backToMenu();
		}
	}
}
