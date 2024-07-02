#include "../../libOne/inc/libOne.h"
#include "../MAIN/MAIN.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "GAME05.h"
namespace GAME05
{
	int GAME::create() {
		Takara2_1Img = loadImage("..\\main\\assets\\game05\\takarabako2.png");
		Takara2_2Img = loadImage("..\\main\\assets\\game05\\takarabako2.png");
		Takara2_3Img = loadImage("..\\main\\assets\\game05\\takarabako2.png");
		Takara2_4Img = loadImage("..\\main\\assets\\game05\\takarabako2.png");
		Takara2_5Img = loadImage("..\\main\\assets\\game05\\takarabako2.png");
		Takara2_6Img = loadImage("..\\main\\assets\\game05\\takarabako2.png");
		Takara2_7Img = loadImage("..\\main\\assets\\game05\\takarabako2.png");
		Takara2_8Img = loadImage("..\\main\\assets\\game05\\takarabako2.png");
		Takara2_9Img = loadImage("..\\main\\assets\\game05\\takarabako2.png");
		Takara2_10Img = loadImage("..\\main\\assets\\game05\\takarabako2.png");
		TakaraImg = loadImage("..\\main\\assets\\game05\\takarabako.png");
		KizaruImg = loadImage("..\\main\\assets\\game05\\kizaru.png");
		GachaImg = loadImage("..\\main\\assets\\game05\\gacha.png");
		TitleImg = loadImage("..\\main\\assets\\game05\\title.png");
		PunchImg = loadImage("..\\main\\assets\\game05\\punch.png");
		LuffyImg = loadImage("..\\main\\assets\\game05\\luffy.png");
		BlockImg = loadImage("..\\main\\assets\\game05\\block.png");
		Tama2Img = loadImage("..\\main\\assets\\game05\\tama2.png");
		HitImg = loadImage("..\\main\\assets\\game05\\punch2.png");
		TamaImg = loadImage("..\\main\\assets\\game05\\tama.png");
		EnelImg = loadImage("..\\main\\assets\\game05\\enel.png");
		BackImg = loadImage("..\\main\\assets\\game05\\back.png");
		WhiteImg = loadImage("..\\main\\assets\\game05\\white.png");
		

		LgSnd = loadSound("..\\main\\assets\\game05\\w006.wav");
		GetSnd = loadSound("..\\main\\assets\\game05\\get.wav");
		BgmSnd = loadSound("..\\main\\assets\\game05\\bgm.wav");
		HitSnd = loadSound("..\\main\\assets\\game05\\hit1.wav");
		LastSnd = loadSound("..\\main\\assets\\game05\\w005.wav");
		OverSnd = loadSound("..\\main\\assets\\game05\\over.wav");
		PunchSnd = loadSound("..\\main\\assets\\game05\\ouda.wav");
		WinSnd = loadSound("..\\main\\assets\\game05\\YouWin.wav");
		TitleSnd = loadSound("..\\main\\assets\\game05\\y014.wav");
		ClickSnd = loadSound("..\\main\\assets\\game05\\click.wav");
		LuckySnd = loadSound("..\\main\\assets\\game05\\lucky.wav");
		ClearSnd = loadSound("..\\main\\assets\\game05\\clear.wav");
		UseSnd = loadSound("..\\main\\assets\\game05\\金額表示.wav");
		FinishSnd = loadSound("..\\main\\assets\\game05\\finish.wav");
		AttackSnd = loadSound("..\\main\\assets\\game05\\attack.wav");
		LGClearSnd = loadSound("..\\main\\assets\\game05\\clear2.wav");
		OpenSnd = loadSound("..\\main\\assets\\game05\\宝箱を開ける.wav");
		AtariSnd = loadSound("..\\main\\assets\\game05\\ジャジャーン.wav");
		ToppaSnd = loadSound("..\\main\\assets\\game05\\イヤッホー！.wav");
		ChoiceSnd = loadSound("..\\main\\assets\\game05\\選択してください.wav");

		return 0;
	}

	void GAME::destroy() {
	}

	void GAME::proc() {
		if (State == TITLE)Title();
		else if (State == RULE)Rule();
		else if (State == VOL)Vol();
		else if (State == GACHA)Gacha();
		else if (State == PROB)Prob();
		else if (State == MEAN)Mean();
		else if (State == BOX)Box();
		else if (State == RESULT)Result();
		else if (State == RESULT2)Result2();
		else if (State == PLAY)Play();
		else if (State == PLAY2)Play2();
		else if (State == PLAY3)Play3();
		else if (State == LUCKY)Lucky();
		else if (State == LUCKYGAME)LuckyGame();
		else if (State == CLEAR)Clear();
		else if (State == ALLCLEAR)Allclear();
		else if (State == LGCLEAR)Lgclear();
		else if (State == LGCLEAR2)Lgclear2();
		else if (State == LGCLEAR3)Lgclear3();
		else if (State == FINISH)Finish();
		else if (State == OVER)Over();
		/*
		textSize(50);
		fill(255, 255, 0);
		text("GAME05", 0, 100);
		*/
	}

	void GAME::Title() {
		clear(0);
		rectMode(CORNER);
		image(TitleImg, 0, 0);
		fill(255, 0, 0);
		textSize(90);
		text("赤", 50, 200);
		fill(0);
		text("文字のポイントをピッタリ取ったらクリア", 150, 200);
		fill(255, 200, 0);
		textSize(100);
		text("～操作説明～", 630, 400);
		text("A:左移動", 500, 600);
		text("D:右移動", 970, 600);
		text("W:上移動", 500, 800);
		text("S:下移動", 970, 800);
		fill(0);
		text("左クリックで遊び方", 500, 1000);

		if (loopBgm) {
			playLoopSound(TitleSnd);
			loopBgm = false;
		}

		if (isTrigger(MOUSE_LBUTTON)) {
			ShowCursor(0);
			State = RULE;
			return;
		}
		setVolume(GetSnd, -(100 - volume2) * (100 - volume2));
		setVolume(PunchSnd, -(100 - volume2) * (100 - volume2));
		setVolume(ClearSnd, -(100 - volume1) * (100 - volume1));
		setVolume(BgmSnd, -(100 - volume1) * (100 - volume1));
		setVolume(OverSnd, -(100 - volume1) * (100 - volume1));
		setVolume(LuckySnd, -(100 - volume2) * (100 - volume2));
		setVolume(LGClearSnd, -(100 - volume1) * (100 - volume1));
		setVolume(LgSnd, -(100 - volume1) * (100 - volume1));
		setVolume(FinishSnd, -(100 - volume2) * (100 - volume2));
		setVolume(AttackSnd, -(100 - volume2) * (100 - volume2));
		setVolume(ClickSnd, -(100 - volume2) * (100 - volume2));
		setVolume(TitleSnd, -(100 - volume1) * (100 - volume1));
		setVolume(ToppaSnd, -(100 - volume2) * (100 - volume2));

		fill(255);
		textSize(50);
		text("Sキー:音量調節", 0, 980);
		if (isTrigger(KEY_S)) {
			Init3();
			State = VOL;
		}

		text("Gキー:ガチャ", 0, 880);
		if (isTrigger(KEY_G)) {
			playSound(ChoiceSnd);
			State = GACHA;
		}

		text("ENTERキーでメニューに戻る", 0, 1080);
		if (isTrigger(KEY_ENTER)) {
			showCursor();
			main()->backToMenu();
		}
	}

	void GAME::Vol() {
		clear(255);
		fill(50);
		textSize(50);
		text("BGM", width / 5.0, height / 3.0);
		text("S E", width / 5.0, height / 2.0);


		if (isTrigger(KEY_B)) {
			adjustment = true;
			cnt = 0;
		}
		if (isTrigger(KEY_S)) {
			adjustment = false;
			cnt = 0;
		}

		strokeWeight(5.0);
		stroke(100);
		fill(0);
		line(width / 3.5, height / 3.15, width / 3.5 + 800, height / 3.15);
		line(width / 3.5, height / 2.05, width / 3.5 + 800, height / 2.05);
		circle(width / 3.5 + volume1 * 8.0, height / 3.15, 25);
		circle(width / 3.5 + volume2 * 8.0, height / 2.05, 25);

		fill(0);
		text((let)volume1, width / 1.4, height / 3.0);
		text((let)volume2, width / 1.4, height / 2.0);
		text("Bキー:BGMに点が移る", 150, 700);
		text("Sキー:SEに点が移る", 1050, 700);
		text("Uキー:BGMまたはSEの音量を上げる", 150, 850);
		text("Dキー:BGMまたはSEの音量を下げる", 1050, 850);

		if (adjustment == true) {
			cnt++;
			if (cnt % 3 == 0) {
				if (volume1 >= 0 && volume1 <= 100) {
					if (isPress(KEY_D)) {
						volume1--;
						if (volume1 < 0) {
							volume1 = 0;
						}
					}
					if (isPress(KEY_U)) {
						volume1++;
						if (volume1 > 100) {
							volume1 = 100;
						}
					}
				}
				cnt = 0;
			}
			fill(255, 0, 255);
			circle(width / 3.5 + volume1 * 8.0, height / 3.15, 25);
		}

		if (adjustment == false) {
			cnt++;
			if (cnt % 3 == 0) {
				if (volume2 >= 0 && volume2 <= 100) {
					if (isPress(KEY_D)) {
						volume2--;
						if (volume2 < 0) {
							volume2 = 0;
						}
					}
					if (isPress(KEY_U)) {
						volume2++;
						if (volume2 > 100) {
							volume2 = 100;
						}
					}
				}
				cnt = 0;
			}
			fill(255, 0, 255);
			circle(width / 3.5 + volume2 * 8.0, height / 2.05, 25);
		}
		setVolume(GetSnd, -(100 - volume2) * (100 - volume2));
		setVolume(PunchSnd, -(100 - volume2) * (100 - volume2));
		setVolume(ClearSnd, -(100 - volume1) * (100 - volume1));
		setVolume(BgmSnd, -(100 - volume1) * (100 - volume1));
		setVolume(OverSnd, -(100 - volume1) * (100 - volume1));
		setVolume(LuckySnd, -(100 - volume2) * (100 - volume2));
		setVolume(LGClearSnd, -(100 - volume1) * (100 - volume1));
		setVolume(LgSnd, -(100 - volume1) * (100 - volume1));
		setVolume(FinishSnd, -(100 - volume2) * (100 - volume2));
		setVolume(AttackSnd, -(100 - volume2) * (100 - volume2));
		setVolume(ClickSnd, -(100 - volume2) * (100 - volume2));
		setVolume(TitleSnd, -(100 - volume1) * (100 - volume1));
		setVolume(ToppaSnd, -(100 - volume2) * (100 - volume2));

		fill(0);
		textSize(50);
		text("Aキーで音を鳴らす", 700, 1080);
		if (isTrigger(KEY_A)) {
			playSound(ClickSnd);
		}

		fill(0);
		textSize(50);
		text("ENTERキーでタイトルに戻る", 0, 1080);
		if (isTrigger(KEY_ENTER)) {
			State = TITLE;
		}
	}

	void GAME::Rule() {
		clear(0);
		rectMode(CORNER);
		image(TitleImg, 0, 0);
		fill(255, 200, 0);
		textSize(50);
		text("～遊び方～", 800, 50);
		textSize(80);
		text("左から敵がランダムに出てくる", 270, 150);
		text("下に書いてあるポイントの範囲内で", 270, 280);
		text("敵に触れたらそのポイント分ゲット！", 270, 370);
		fill(255, 0, 0);
		text("赤", 270, 520);
		fill(255, 200, 0);
		text("文字のポイントをカウント以内に", 350, 520);
		text("ゲットできたらゲームクリア", 270, 620);
		text("カウントが0になるか", 270, 780);
		fill(255, 0, 0);
		text("赤", 1030, 780);
		fill(255, 200, 0);
		text("文字のポイントより", 1110, 780);
		text("多く取ったらゲームオーバー", 270, 880);
		text("左クリックでゲームスタート", 270, 1030);
		if (isTrigger(MOUSE_LBUTTON)) {
			Init();
			Init3();
			stopSound(TitleSnd);
			playLoopSound(BgmSnd);
			ShowCursor(0);
			State = PLAY;
			return;
		}

		if (isTrigger(KEY_B)) {
			stopSound(TitleSnd);
			playSound(LuckySnd);
			State = LUCKY;
			return;
		}

		fill(255);
		textSize(50);
		text("ENTERキー:タイトルに戻る", 0, 1080);
		if (isTrigger(KEY_ENTER)) {
			State = TITLE;
		}
	}

	void GAME::Init() {
		PPx = width / 2;
		PPy = height / 2;
		PVx = 20.0f;
		PVy = 20.0f;
		PMx = 140.0f;
		PMy = 175.0f;
		PhalfW = 20.0f;
		PhalfH = 20.0f;

		EPx = -10;
		EPy = 150.0f;
		EVx = 30.0f;
		EMx = 140.0f;
		EhalfW = 20.0f;
		EhalfH = 20.0f;
		EHp = 1;

		GPR = 50;
		GPRx = 384;
		GPRy = 1080;

		GPY = 30;
		GPYx = 768;
		GPYy = 1080;

		GPB = 10;
		GPBx = 1152;
		GPBy = 1080;

		GPG = 5;
		GPGx = 1536;
		GPGy = 1080;

		GPP = 1;
		GPPx = 1920;
		GPPy = 1080;

		Point = 0;

		CountDown = 60 * 60;

		CountDown3 = 50 * 60;

		CountDown4 = 45 * 60;

		ClearPoint = random() % 100 + 1.0f;

		ClearPoint2 = random() % 70 + 1.0f;

		ClearPoint3 = random() % 50 + 1.0f;

		LuckyNo = random() % 5 + 1.0f;

		PointFlag = false;

		adjustment = true;
	}

	void GAME::Init2() {
		//プレイヤー情報
		Px = width / 2;
		Py = 930;
		halfW = 100;
		halfH = 200;
		Mx = 120;
		Vx = 15;
		HP = 50;
		MaxHp = HP;

		//プレイヤーの弾
		PBPx = Px;
		PBPy = Py;
		PBVy = -25;
		PBHp = 0;
		PBhalfW = 10;
		PBhalfH = 20;
		PBOfstY = -110;

		//敵情報
		EPx = 100;
		EPy = 250;
		EhalfW = 100;
		EhalfH = 100;
		EVx = 23.0f;
		EHP = 500;

		//敵の弾
		EBPx = EPx;
		EBPy = EPy;
		EBVy = 30;
		EBHp = 0;
		EBhalfW = 10;
		EBhalfH = 20;
		OfstY = -110;

		//プレイヤー、敵のHP情報
		HpX = 1400;
		HpY = 1030;

		EHpX = 970;
		EHpY = 80;
		EMaxHp = EHP;

		EhpGaugeOfsY = -180;

		hpGaugeWidth = 30;

		EHpWarning = EHP * 0.3f;
		EHpDenger = EHP * 0.1f;

		HpWarning = EHP * 0.03f;
		HpDenger = EHP * 0.01f;

		SpDire = HP * 0.7;

		Dire = HP * 0.6;

		img = PunchImg;

		CountDown = 40 * 60;

		EHitFlag = false;

		PHitFlag = false;

		adjustment = true;
	}

	void GAME::Init3() {
		cnt = 0;
		adjustment = true;
	}

	void GAME::Init4()
	{
		num0 = random() % 100 + 1;
		num1 = random() % 100 + 1;
		num2 = random() % 100 + 1;
		num3 = random() % 100 + 1;
		num4 = random() % 100 + 1;
		num5 = random() % 100 + 1;
		num6 = random() % 100 + 1;
		num7 = random() % 100 + 1;
		num8 = random() % 100 + 1;
		num9 = random() % 100 + 1;
		num10 = random() % 100 + 1;

		LTcnt = random() % 7 + 1;
		gachaCnt = 0;

		star4Total = 10;
		star5Total = 9;
		star6Total = 7;
		sstar6Total = 6;

		star4Total1 = 10;
		star5Total1 = 9;
		star6Total1 = 7;
		sstar6Total1 = 6;

		star4Total2 = 10;
		star5Total2 = 9;
		star6Total2 = 7;
		sstar6Total2 = 6;

		star4Total3 = 10;
		star5Total3 = 9;
		star6Total3 = 7;
		sstar6Total3 = 6;

		star4Total4 = 10;
		star5Total4 = 9;
		star6Total4 = 7;
		sstar6Total4 = 6;

		star4Total5 = 10;
		star5Total5 = 9;
		star6Total5 = 7;
		sstar6Total5 = 6;

		star4Total6 = 10;
		star5Total6 = 9;
		star6Total6 = 7;
		sstar6Total6 = 6;

		star4Total7 = 10;
		star5Total7 = 9;
		star6Total7 = 7;
		sstar6Total7 = 6;

		star4Total8 = 10;
		star5Total8 = 9;
		star6Total8 = 7;
		sstar6Total8 = 6;

		star4Total9 = 10;
		star5Total9 = 9;
		star6Total9 = 7;
		sstar6Total9 = 6;

		star4Total10 = 10;
		star5Total10 = 9;
		star6Total10 = 7;
		sstar6Total10 = 6;
		takaraHp = 1;

		randomsstar6num = random() % sstar6Total;
		randomstar6num = random() % star6Total;
		randomstar5num = random() % star5Total;
		randomstar4num = random() % star4Total;

		randomsstar6num1 = random() % sstar6Total1;
		randomstar6num1 = random() % star6Total1;
		randomstar5num1 = random() % star5Total1;
		randomstar4num1 = random() % star4Total1;

		randomsstar6num2 = random() % sstar6Total2;
		randomstar6num2 = random() % star6Total2;
		randomstar5num2 = random() % star5Total2;
		randomstar4num2 = random() % star4Total2;

		randomsstar6num3 = random() % sstar6Total3;
		randomstar6num3 = random() % star6Total3;
		randomstar5num3 = random() % star5Total3;
		randomstar4num3 = random() % star4Total3;

		randomsstar6num4 = random() % sstar6Total4;
		randomstar6num4 = random() % star6Total4;
		randomstar5num4 = random() % star5Total4;
		randomstar4num4 = random() % star4Total4;

		randomsstar6num5 = random() % sstar6Total5;
		randomstar6num5 = random() % star6Total5;
		randomstar5num5 = random() % star5Total5;
		randomstar4num5 = random() % star4Total5;

		randomsstar6num6 = random() % sstar6Total6;
		randomstar6num6 = random() % star6Total6;
		randomstar5num6 = random() % star5Total6;
		randomstar4num6 = random() % star4Total6;

		randomsstar6num7 = random() % sstar6Total7;
		randomstar6num7 = random() % star6Total7;
		randomstar5num7 = random() % star5Total7;
		randomstar4num7 = random() % star4Total7;

		randomsstar6num8 = random() % sstar6Total8;
		randomstar6num8 = random() % star6Total8;
		randomstar5num8 = random() % star5Total8;
		randomstar4num8 = random() % star4Total8;

		randomsstar6num9 = random() % sstar6Total9;
		randomstar6num9 = random() % star6Total9;
		randomstar5num9 = random() % star5Total9;
		randomstar4num9 = random() % star4Total9;

		randomsstar6num10 = random() % sstar6Total10;
		randomstar6num10 = random() % star6Total10;
		randomstar5num10 = random() % star5Total10;
		randomstar4num10 = random() % star4Total10;
	}

	void GAME::Play() {
		clear(200);
		if (isPress(KEY_D)) { PPx += PVx; }
		if (isPress(KEY_A)) { PPx += -PVx; }
		if (isPress(KEY_S)) { PPy += PVy; }
		if (isPress(KEY_W)) { PPy += -PVy; }

		if (PPx < PMx) {
			PPx = PMx;
		}
		if (PPx > width - PMx) {
			PPx = width - PMx;
		}
		if (PPy < PMy) {
			PPy = PMy;
		}
		if (PPy > height - PMy) {
			PPy = height - PMy;
		}

		EPx += EVx;
		if (EPx > 1980) {
			EPx = -10;
			EPy = random() % 780 + 150.0f;
		}

		if (EPx > width) {
			PointFlag = false;
		}
		//各ポイントの範囲と獲得ポイント
		if (PointFlag == false) {
			if (collision() && EPx < GPRx && PPx < GPRx) {
				playSound(GetSnd);
				Point += GPR;
				PointFlag = true;
			}
			if (collision() && EPx < GPYx && EPx > GPRx && PPx < GPYx && PPx > GPRx) {
				playSound(GetSnd);
				Point += GPY;
				PointFlag = true;
			}
			if (collision() && EPx < GPBx && EPx > GPYx && PPx < GPBx && PPx > GPYx) {
				playSound(GetSnd);
				Point += GPB;
				PointFlag = true;
			}
			if (collision() && EPx < GPGx && EPx > GPBx && PPx < GPGx && PPx > GPBx) {
				playSound(GetSnd);
				Point += GPG;
				PointFlag = true;
			}
			if (collision() && EPx < GPPx && EPx > GPGx && PPx < GPPx && PPx > GPGx) {
				playSound(GetSnd);
				Point += GPP;
				PointFlag = true;
			}
		}
		//クリア、ゲームオーバー条件
		if (Point == ClearPoint && CountDown > 0) {
			stopSound(GetSnd);
			stopSound(BgmSnd);
			playSound(ToppaSnd);
			StageCount++;// = StageCount += 1;
			State = CLEAR;
		}
		if (Point > ClearPoint || CountDown <= 0) {
			stopSound(BgmSnd);
			stopSound(GetSnd);
			playSound(OverSnd);
			State = OVER;
		}
		//描画
		draw();

		if (CountDown > 0) {
			fill(0);
			CountDown -= delta;
			textSize(100);
			text(CountDown / 60, 0, 300);
		}

		if (isTrigger(KEY_R)) {
			stopSound(BgmSnd);
			State = RULE;
		}
	}

	void GAME::Play2() {
		clear(200);
		if (isPress(KEY_D)) { PPx += PVx; }
		if (isPress(KEY_A)) { PPx += -PVx; }
		if (isPress(KEY_S)) { PPy += PVy; }
		if (isPress(KEY_W)) { PPy += -PVy; }

		if (PPx < PMx) {
			PPx = PMx;
		}
		if (PPx > width - PMx) {
			PPx = width - PMx;
		}
		if (PPy < PMy) {
			PPy = PMy;
		}
		if (PPy > height - PMy) {
			PPy = height - PMy;
		}

		EPx += EVx;
		if (EPx > 1980) {
			EPx = -10;
			EPy = random() % 780 + 150.0f;
		}

		if (EPx > width) {
			PointFlag = false;
		}
		//各ポイントの範囲と獲得ポイント
		if (PointFlag == false) {
			if (collision() && EPx < GPRx && PPx < GPRx) {
				playSound(GetSnd);
				Point += GPR;
				PointFlag = true;
			}
			if (collision() && EPx < GPYx && EPx > GPRx && PPx < GPYx && PPx > GPRx) {
				playSound(GetSnd);
				Point += GPY;
				PointFlag = true;
			}
			if (collision() && EPx < GPBx && EPx > GPYx && PPx < GPBx && PPx > GPYx) {
				playSound(GetSnd);
				Point += GPB;
				PointFlag = true;
			}
			if (collision() && EPx < GPGx && EPx > GPBx && PPx < GPGx && PPx > GPBx) {
				playSound(GetSnd);
				Point += GPG;
				PointFlag = true;
			}
			if (collision() && EPx < GPPx && EPx > GPGx && PPx < GPPx && PPx > GPGx) {
				playSound(GetSnd);
				Point += GPP;
				PointFlag = true;
			}
		}

		//クリア、ゲームオーバー条件
		if (Point == ClearPoint2 && CountDown3 > 0) {
			stopSound(GetSnd);
			stopSound(BgmSnd);
			playSound(ToppaSnd);
			State = CLEAR;
		}
		if (Point > ClearPoint2 || CountDown3 == 0) {
			stopSound(BgmSnd);
			stopSound(GetSnd);
			playSound(OverSnd);
			State = OVER;
		}
		//描画
		draw();

		if (CountDown3 > 0) {
			fill(0);
			CountDown3 -= delta;
			textSize(100);
			text(CountDown3 / 60, 0, 300);
		}

		if (isTrigger(KEY_R)) {
			stopSound(BgmSnd);
			State = RULE;
		}
	}

	void GAME::Play3() {
		clear(200);
		if (isPress(KEY_D)) { PPx += PVx; }
		if (isPress(KEY_A)) { PPx += -PVx; }
		if (isPress(KEY_S)) { PPy += PVy; }
		if (isPress(KEY_W)) { PPy += -PVy; }

		if (PPx < PMx) {
			PPx = PMx;
		}
		if (PPx > width - PMx) {
			PPx = width - PMx;
		}
		if (PPy < PMy) {
			PPy = PMy;
		}
		if (PPy > height - PMy) {
			PPy = height - PMy;
		}

		EPx += EVx;
		if (EPx > 1980) {
			EPx = -10;
			EPy = random() % 780 + 150.0f;
		}

		if (EPx > width) {
			PointFlag = false;
		}
		//各ポイントの範囲と獲得ポイント
		if (PointFlag == false) {
			if (collision() && EPx < GPRx && PPx < GPRx) {
				playSound(GetSnd);
				Point += GPR;
				PointFlag = true;
			}
			if (collision() && EPx < GPYx && EPx > GPRx && PPx < GPYx && PPx > GPRx) {
				playSound(GetSnd);
				Point += GPY;
				PointFlag = true;
			}
			if (collision() && EPx < GPBx && EPx > GPYx && PPx < GPBx && PPx > GPYx) {
				playSound(GetSnd);
				Point += GPB;
				PointFlag = true;
			}
			if (collision() && EPx < GPGx && EPx > GPBx && PPx < GPGx && PPx > GPBx) {
				playSound(GetSnd);
				Point += GPG;
				PointFlag = true;
			}
			if (collision() && EPx < GPPx && EPx > GPGx && PPx < GPPx && PPx > GPGx) {
				playSound(GetSnd);
				Point += GPP;
				PointFlag = true;
			}
		}

		//クリア、ゲームオーバー, ラッキーゲーム出現条件
		if (Point == ClearPoint3 && CountDown4 > 0) {
			stopSound(GetSnd);
			stopSound(BgmSnd);
			playSound(ToppaSnd);
			State = CLEAR;
		}
		if (Point == ClearPoint3 && CountDown4 > 0 && LuckyNo != 1) {
			stopSound(GetSnd);
			stopSound(ToppaSnd);
			stopSound(BgmSnd);
			playSound(ClearSnd);
			tamaCnt += 3;
			State = ALLCLEAR;
		}
		if (Point == ClearPoint3 && CountDown4 > 0 && LuckyNo == 1) {
			stopSound(BgmSnd);
			stopSound(TitleSnd);
			stopSound(GetSnd);
			stopSound(ToppaSnd);
			playSound(LuckySnd);
			tamaCnt += 3;
			ShowCursor(0);
			Init3();
			State = LUCKY;
		}
		if (Point > ClearPoint3 || CountDown4 == 0) {
			stopSound(BgmSnd);
			stopSound(GetSnd);
			playSound(OverSnd);
			State = OVER;
		}
		//描画
		draw();

		if (CountDown4 > 0) {
			fill(0);
			CountDown4 -= delta;
			textSize(100);
			text(CountDown4 / 60, 0, 300);
		}

		if (isTrigger(KEY_R)) {
			stopSound(BgmSnd);
			State = RULE;
		}
	}

	void GAME::Clear() {
		if (StageCount == 1) {
			clear(35, 253, 59);
			fill(255);
			textSize(100);
			text("1ステージ目クリア", 560, 300);
			text("左クリックで2ndStageへ", 420, 500);
			text("敵と自分のスピードがアップ", 340, 700);
			textSize(50);
			text("ガチャ玉1個ゲット!", 0, 1080);
			if (isTrigger(MOUSE_LBUTTON)) {
				Init();
				StageCount++;
				PVx += 5.0f;
				PVy += 5.0f;
				EVx += 10.0f;
				ClearPoint = ClearPoint2;
				playLoopSound(BgmSnd);
				stopSound(ToppaSnd);
				tamaCnt += 1;
				State = PLAY2;
			}
		}
		else if (StageCount == 2) {
			clear(252, 230, 50);
			fill(255);
			textSize(100);
			text("2ステージ目クリア", 560, 300);
			text("左クリックでLastStageへ", 400, 500);
			text("敵と自分のスピードが更にアップ", 250, 700);
			textSize(50);
			text("ガチャ玉2個ゲット!", 0, 1080);
			if (isTrigger(MOUSE_LBUTTON)) {
				Init();
				StageCount++;
				PVx += 10.0f;
				PVy += 10.0f;
				EVx += 15.0f;
				ClearPoint = ClearPoint3;
				playLoopSound(BgmSnd);
				stopSound(ToppaSnd);
				tamaCnt += 2;
				State = PLAY3;
			}
		}
	}

	void GAME::Allclear() {
		clear(255);
		fill(255, 0, 0);
		textSize(300);
		text("A", 200, 600);
		fill(253, 135, 35);
		text("L", 400, 600);
		fill(252, 253, 35);
		text("L", 600, 600);
		fill(164, 253, 35);
		text("C", 850, 600);
		fill(35, 253, 59);
		text("L", 1050, 600);
		fill(35, 253, 205);
		text("E", 1250, 600);
		fill(35, 74, 253);
		text("A", 1450, 600);
		fill(209, 35, 253);
		text("R", 1650, 600);
		textSize(100);
		fill(213, 202, 112);
		text("Congratulations", 600, 800);
		textSize(50);
		fill(0);
		text("左クリックでタイトルに戻ります", 0, 1080);
		text("ガチャ玉3個ゲット!", 0, 980);
		if (isTrigger(MOUSE_LBUTTON)) {
			stopSound(ClearSnd);
			playLoopSound(TitleSnd);
			StageCount = 0;
			State = TITLE;
			return;
		}
	}

	void GAME::Lucky() {
		clear(236, 215, 98);
		fill(0);
		textSize(100);
		text("ゲームクリア!", 630, 100);
		text("ラッキーゲーム！", 600, 200);
		text("パンチを当てて", 600, 300);
		text("時間内に敵を倒そう!", 500, 400);
		text("～操作方法～", 650, 600);
		text("A:左移動", 500, 700);
		text("D:右移動", 1000, 700);
		text("左クリックで弾発射", 500, 800);
		text("左クリック長押しで自動発射", 320, 900);
		text("左クリックでゲーム画面に移行", 300, 1000);
		textSize(50);
		text("ガチャ玉3個ゲット!", 0, 1080);

		if (isTrigger(MOUSE_LBUTTON)) {
			Init2();
			Init3();
			Init4();
			CountDown2 -= delta;
			text(CountDown, width / 2, height / 2);
			playLoopSound(LgSnd);
			State = LUCKYGAME;
			return;
		}
	}

	void GAME::LuckyGame() {
		if (isPress(KEY_D)) {
			Px += Vx;
		}
		if (isPress(KEY_A)) {
			Px += -Vx;
		}
		if (Px < Mx) {
			Px = Mx;
		}
		if (Px > width - Mx) {
			Px = width - Mx;
		}
		//パンチ
		if (isPress(MOUSE_LBUTTON)) {
			if (PBHp == 0) {
				PBHp = 1;
				PBPx = Px;
				PBPy = Py + PBOfstY;
			}
		}
		if (PBHp > 0) {
			PBPy += PBVy;
			if (PBPy < -PBH) {
				PBHp = 0;
			}
		}
		//敵の弾発射
		if (EBHp == 0) {
			EBPx = EPx;
			EBPy = EPy + EBOfstY;
			EBHp = 1;
		}
		if (EBHp > 0) {
			EBPy += EBVy;
			if (EBPy > height + EBhalfH) {
				EBHp = 0;
			}
		}

		//敵の移動
		EPx += EVx;
		if (EPx < EhalfW ||
			EPx > width - EhalfW) {
			EVx = -EVx;
		}

		if (PBHp == 0) {
			EHitFlag = false;
		}

		if (EHitFlag == false) {
			if (collision2()) {
				playSound(PunchSnd);
				img = HitImg;
				EHP -= 25;
				EHitFlag = true;
			}
		}
		else {
			img = PunchImg;
		}

		if (EBHp <= 0) {
			PHitFlag = false;
		}

		if (PHitFlag == false) {
			if (collision3()) {
				playSound(AttackSnd);
				HP -= 3;
				PHitFlag = true;
			}
		}

		if (EHP <= 0 && HP >= SpDire && LTcnt != 1) {
			stopSound(LgSnd);
			stopSound(PunchSnd);
			stopSound(AttackSnd);
			playSound(LGClearSnd);
			tamaCnt += 15;
			State = LGCLEAR;
		}

		if (EHP <= 0 && HP >= SpDire && LTcnt == 1) {
			stopSound(LgSnd);
			stopSound(PunchSnd);
			stopSound(AttackSnd);
			playSound(LGClearSnd);
			tamaCnt += 50;
			State = LGCLEAR3;
		}

		if (EHP <= 0 && HP <= Dire) {
			stopSound(LgSnd);
			stopSound(AttackSnd);
			stopSound(PunchSnd);
			stopSound(LGClearSnd);
			playSound(WinSnd);
			tamaCnt += 10;
			State = LGCLEAR2;
		}


		if (HP <= 0 || CountDown <= 0) {
			stopSound(LgSnd);
			stopSound(PunchSnd);
			stopSound(AttackSnd);
			playSound(FinishSnd);
			State = FINISH;
		}
		//描画
		draw2();

		if (CountDown > 0) {
			fill(0);
			CountDown -= delta;
			textSize(100);
			text(CountDown / 60, 0, 300);
		}
	}

	void GAME::Lgclear() {
		clear(255, 255, 255);
		textSize(250);
		fill(255, 72, 72);
		text("L", 50, height / 2);
		fill(255, 161, 72);
		text("U", 150, height / 2);
		fill(255, 203, 72);
		text("C", 260, height / 2);
		fill(250, 255, 72);
		text("K", 370, height / 2);
		fill(200, 255, 72);
		text("Y", 490, height / 2);
		fill(100, 255, 72);
		text("G", 590, height / 2);
		fill(100, 255, 72);
		text("A", 710, height / 2);
		fill(72, 255, 185);
		text("M", 830, height / 2);
		fill(72, 255, 250);
		text("E", 950, height / 2);
		fill(72, 200, 255);
		text("C", 1270, height / 2);
		fill(72, 190, 255);
		text("L", 1390, height / 2);
		fill(72, 100, 255);
		text("E", 1510, height / 2);
		fill(130, 72, 255);
		text("A", 1630, height / 2);
		fill(220, 72, 255);
		text("R", 1750, height / 2);
		textSize(50);
		text("ガチャ玉15個ゲット!", 0, 980);
		if (isTrigger(MOUSE_LBUTTON)) {
			stopSound(LGClearSnd);
			playLoopSound(TitleSnd);
			StageCount = 0;
			State = TITLE;
			return;
		}
		fill(0);
		textSize(50);
		text("左クリックでタイトルに戻る", 0, 1080);
	}

	void GAME::Lgclear2()
	{
		clear(255, 255, 255);
		textSize(250);
		fill(255, 0, 0);
		text("LUCKYGAME CLEAR", 50, height / 2);
		fill(0);
		textSize(50);
		text("左クリックでタイトルに戻る", 0, 1080);
		text("ガチャ玉10個ゲット!", 0, 980);
		if (isTrigger(MOUSE_LBUTTON)) {
			stopSound(WinSnd);
			playLoopSound(TitleSnd);
			StageCount = 0;
			State = TITLE;
			return;
		}
	}

	void GAME::Lgclear3()
	{
		clear(255, 255, 255);
		image(LuffyImg, width / 2, height / 2);
		textSize(250);
		fill(255, 72, 72);
		text("L", 50, 300);
		fill(255, 161, 72);
		text("U", 150, 300);
		fill(255, 203, 72);
		text("C", 260, 300);
		fill(250, 255, 72);
		text("K", 370, 300);
		fill(200, 255, 72);
		text("Y", 490, 300);
		fill(100, 255, 72);
		text("G", 590, 300);
		fill(100, 255, 72);
		text("A", 710, 300);
		fill(72, 255, 185);
		text("M", 830, 300);
		fill(72, 255, 250);
		text("E", 950, 300);
		fill(72, 200, 255);
		text("C", 1270, 300);
		fill(72, 190, 255);
		text("L", 1390, 300);
		fill(72, 100, 255);
		text("E", 1510, 300);
		fill(130, 72, 255);
		text("A", 1630, 300);
		fill(220, 72, 255);
		text("R", 1750, 300);
		textSize(50);
		fill(213, 202, 112);
		text("ガチャ玉50個ゲット!", 0, 980);
		if (isTrigger(MOUSE_LBUTTON)) {
			stopSound(LGClearSnd);
			playLoopSound(TitleSnd);
			StageCount = 0;
			State = TITLE;
			return;
		}
		fill(0);
		textSize(50);
		text("左クリックでタイトルに戻る", 0, 1080);
	}

	void GAME::Finish() {
		clear(0, 200, 255);
		image(LuffyImg, 600, height / 2);
		image(EnelImg, 1200, height / 2);
		fill(255);
		textSize(250);
		text("FINISH!", 500, 300);
		if (isTrigger(MOUSE_LBUTTON)) {
			playLoopSound(TitleSnd);
			StageCount = 0;
			State = TITLE;
			return;
		}
		fill(255);
		textSize(50);
		text("左クリックでタイトルに戻る", 0, 1080);
	}

	void GAME::Over() {
		clear(0);
		image(EnelImg, EPx = width / 2, EPy = height / 2);
		fill(255);
		textSize(200);
		text("Game Over", 500, 300);
		fill(255);
		textSize(50);
		text("左クリックでタイトルに戻る", 0, 1080);
		if (isTrigger(MOUSE_LBUTTON)) {
			playLoopSound(TitleSnd);
			stopSound(OverSnd);
			StageCount = 0;
			State = TITLE;
		}
	}

	void GAME::Gacha() {
		clear();
		rectMode(CORNER);
		image(GachaImg, 0, 0);
		rectMode(CENTER);
		image(Tama2Img, 1700, 100);
		if (tamaCnt >= 99999) {
			text("99999+", 1730, 120);
		}
		else {
			text((let)tamaCnt, 1730, 120);
		}
		textSize(100);
		fill(0);
		text("Sキー:シングルガチャ 5個消費", 300, 300);
		text("Rキー:10連ガチャ 50個消費", 300, 500);
		text("(シングルガチャはOキー、10連ガチャは", 80, 700);
		text("A, S, D, F, G, H, J, K, L, Pキーを", 80, 800);
		text("押すと1個ずつ結果が出ます)", 80, 900);

		if (isTrigger(KEY_S) && tamaCnt >= 5) {
			Init4();
			playSound(UseSnd);
			tamaCnt -= 5;
			clear(255);
			FreamCount = 120;
			image(TakaraImg, width / 2, height / 2);
			State = RESULT;
		}

		if (isTrigger(KEY_R) && tamaCnt >= 50) {
			Init4();
			playSound(UseSnd);
			tamaCnt -= 50;
			clear(255);
			FreamCount = 1320;
			image(Takara2_1Img, 320, 220);
			image(Takara2_2Img, 970, 220);
			image(Takara2_3Img, 1620, 220);
			image(Takara2_4Img, 320, 420);
			image(Takara2_5Img, 970, 420);
			image(Takara2_6Img, 1620, 420);
			image(Takara2_7Img, 320, 620);
			image(Takara2_8Img, 970, 620);
			image(Takara2_9Img, 1620, 620);
			image(Takara2_10Img, 970, 820);
			State = RESULT2;
		}

		textSize(50);
		text("左クリック:タイトルに戻る", 0, 100);
		if (isTrigger(MOUSE_LBUTTON)) {
			State = TITLE;
		}
		text("Kキー:出現確率", 0, 980);
		if (isTrigger(KEY_K)) {
			State = PROB;
		}
		text("Mキー:ガチャ玉の入手方法", 1300, 980);
		if (isTrigger(KEY_M)) {
			State = MEAN;
		}
		text("Bキー:図鑑", 1300, 1080);
		if (isTrigger(KEY_B)) {
			State = BOX;
		}
	}

	void GAME::Prob()
	{
		clear(255);
		fill(0);
		textSize(60);
		text("☆4:10体:53%", 50, 150);
		textSize(60);
		text("丹羽長秀:5.3%", 50, 260);
		text("今川義元:5.3%", 50, 340);
		text("松永久秀:5.3%", 50, 420);
		text("斎藤道三:5.3%", 50, 500);
		text("浅井長政:5.3%", 50, 580);
		text("前田慶次:5.3%", 50, 660);
		text("井伊直弼:5.3%", 50, 740);
		text("千 利 休:5.3%", 50, 820);
		text("土方歳三:5.3%", 50, 900);
		text("沖田総司:5.3%", 50, 980);

		text("☆5:9体:27%", 490, 150);
		textSize(60);
		text("本田忠勝:3.0%", 490, 260);
		text("前田利家:3.0%", 490, 340);
		text("明智光秀:3.0%", 490, 420);
		text("雑賀孫市:3.0%", 490, 500);
		text("島 左 近:3.0%", 490, 580);
		text("加藤清正:3.0%", 490, 660);
		text("大谷吉継:3.0%", 490, 740);
		text("服部半蔵:3.0%", 490, 820);
		text("葛飾北斎:3.0%", 490, 900);

		text("☆6:7体:14%", 930, 150);
		textSize(60);
		text("伊達政宗:2.0%", 930, 260);
		text("上杉謙信:2.0%", 930, 340);
		text("武田信玄:2.0%", 930, 420);
		text("真田幸村:2.0%", 930, 500);
		text("毛利元就:2.0%", 930, 580);
		text("森 蘭 丸:2.0%", 930, 660);
		text("宮本武蔵:2.0%", 930, 740);

		fill(213, 202, 112);
		text("★6", 1370, 150);
		fill(0);
		text(":6体:6%", 1460, 150);
		textSize(60);
		text("織田信長:1.0%", 1370, 260);
		text("徳川家康:1.0%", 1370, 340);
		text("豊臣秀吉:1.0%", 1370, 420);
		text("坂本龍馬:1.0%", 1370, 500);
		text("西郷隆盛:1.0%", 1370, 580);
		text("聖徳太子:1.0%", 1370, 660);

		textSize(50);
		text("左クリック:ガチャ画面に戻る", 0, 1080);
		text("小数第2位以下は省略", 700, 1080);
		if (isTrigger(MOUSE_LBUTTON)) {
			State = GACHA;
		}
	}

	void GAME::Mean()
	{
		clear(255);
		fill(0);
		textSize(80);
		text("ガチャ玉の入手方法と個数", 450, 100);
		text("①通常のゲームプレイ:6個", 450, 200);
		text("ステージ1突破:1個", 550, 300);
		text("ステージ2突破:2個", 550, 400);
		text("ラストステージ突破:3個", 450, 500);
		text("②ラッキーゲーム:15個 or 10個", 350, 700);
		text("HPを35以上残して勝利:15個", 550, 800);
		text("勝利:10個", 550, 900);
		textSize(50);
		text("左クリック:ガチャ選択画面に戻る", 0, 1080);
		if (isTrigger(MOUSE_LBUTTON)) {
			State = GACHA;
		}
	}

	void GAME::Box() {
		clear(255);
		
		textSize(80);
		for (int i = 0; i < 10; i++) {
			text("☆4", 160, 100);
			text(Name4[i].name, 50, 200 + 90 * i);
			text(Name4[i].GetCnt, 400, 200 + 90 * i);

		}
		for (int i = 0; i < 9; i++) {
			text("☆5", 640, 100);
			text(Name5[i].name, 530, 200 + 90 * i);
			text(Name5[i].GetCnt, 880, 200 + 90 * i);
		}
		for (int i = 0; i < 7; i++) {
			text("☆6", 1120, 100);
			text(Name6[i].name, 1010, 200 + 90 * i);
			text(Name6[i].GetCnt, 1360, 200 + 90 * i);
		}
		for (int i = 0; i < 6; i++) {
			text("★6", 1600, 100);
			text(Name7[i].name, 1490, 200 + 90 * i);
			text(Name7[i].GetCnt, 1840, 200 + 90 * i);
		}

		textSize(50);
		text("左クリック:ガチャ選択画面に戻る", 0, 1080);
		if (isTrigger(MOUSE_LBUTTON)){
			State = GACHA;	   
		}					   
	}						   
							   
	void GAME::Result() {	   
		textSize(50);		   
		text("結果が出て約2秒後にガチャ選択画面に戻る", 0, 1080);
		textSize(250);
		rectMode(CENTER);
		while (notQuit) {
			if (gachaCnt == 1) {
				break;
			}
			if (isTrigger(KEY_O)) {
				TakaraImg = loadImage("..\\main\\assets\\game05\\white2.png");
				image(TakaraImg, width / 2, height / 2);
				playSound(OpenSnd);
				gachaCnt++;
				if (num0 > 94) {
					playSound(AtariSnd);
					fill(213, 202, 112);
					text("★6:", 100, 560);
					fill(0);
					text((let)Name7[randomsstar6num].name, 600, 560);
					Name7[randomsstar6num].GetCnt++;
				}
				else if (num0 > 80) {
					playSound(HitSnd);
					text("☆6:", 100, 560);
					text((let)Name6[randomstar6num].name, 600, 560);
					Name6[randomstar6num].GetCnt++;
				}
				else if (num0 > 53) {
					text("☆5:", 100, 560);
					text((let)Name5[randomstar5num].name, 600, 560);
					Name5[randomstar5num].GetCnt++;
				}
				else {
					text("☆4:", 100, 560);
					text((let)Name4[randomstar4num].name, 600, 560);
					Name4[randomstar4num].GetCnt++;
				}
			}
		}
		FreamCount -= 2;
		if (FreamCount == 0) {
			TakaraImg = loadImage("..\\main\\assets\\game05\\takarabako.png");
			State = GACHA;
		}
	}
	void GAME::Result2() {
		textSize(50);
		fill(0);
		text("すべての結果が出て約3秒後にガチャ選択画面に戻る", 0, 1080);
		textSize(100);
		while (notQuit) {
			if (gachaCnt == 10) {
				break;
			}
			//1
			if (isTrigger(KEY_A)) {
				Takara2_1Img = loadImage("..\\main\\assets\\game05\\white.png");
			    image(Takara2_1Img, 320, 220);
				gachaCnt++;
				playSound(OpenSnd);
				if (num1 > 94) {
					playSound(AtariSnd);
					fill(213, 202, 112);
					text("★6:", 10, 260);
					fill(0);
					text((let)Name7[randomsstar6num1].name, 200, 260);
					chara = randomsstar6num1;
					Name7[chara].GetCnt++;
				}
				else if (num1 > 80) {
					playSound(HitSnd);
					fill(0);
					textSize(100);
					text("☆6:", 10, 260);
					text((let)Name6[randomstar6num1].name, 200, 260);
					chara = randomstar6num1;
					Name6[chara].GetCnt++;
				}
				else if (num1 > 53) {
					fill(0);
					text("☆5:", 10, 260);
					text((let)Name5[randomstar5num1].name, 200, 260);
					chara = randomstar5num1;
					Name5[chara].GetCnt++;
				}
				else {
					fill(0);
					text("☆4:", 10, 260);
					text((let)Name4[randomstar4num1].name, 200, 260);
					chara = randomstar4num1;
					Name4[chara].GetCnt++;
				}
			}
			//2
			if (isTrigger(KEY_S)) {
				Takara2_2Img = loadImage("..\\main\\assets\\game05\\white.png");
				image(Takara2_2Img, 970, 220);
				gachaCnt++;
				playSound(OpenSnd);
				if (num2 > 94) {
					playSound(AtariSnd);
					fill(213, 202, 112);
					text("★6:", 650, 260);
					fill(0);
					text((let)Name7[randomsstar6num2].name, 850, 260);
					chara = randomsstar6num2;
					Name7[chara].GetCnt++;
				}
				else if (num2 > 80) {
					playSound(HitSnd);
					fill(0);
					text("☆6:", 650, 260);
					text((let)Name6[randomstar6num2].name, 850, 260);
					chara = randomstar6num2;
					Name6[chara].GetCnt++;
				}
				else if (num2 > 53) {
					fill(0);
					text("☆5:", 650, 260);
					text((let)Name5[randomstar5num2].name, 850, 260);
					chara = randomstar5num2;
					Name5[chara].GetCnt++;
				}
				else {
					fill(0);
					text("☆4:", 650, 260);
					text((let)Name4[randomstar4num2].name, 850, 260);
					chara = randomstar4num2;
					Name4[chara].GetCnt++;
				}
			}
			//3
			if (isTrigger(KEY_D)) {
				Takara2_3Img = loadImage("..\\main\\assets\\game05\\white.png");
				image(Takara2_3Img, 1620, 220);
				gachaCnt++;
				playSound(OpenSnd);
				if (num3 > 94) {
					playSound(AtariSnd);
					fill(213, 202, 112);
					text("★6:", 1300, 260);
					fill(0);
					text((let)Name7[randomsstar6num3].name, 1500, 260);
					chara = randomsstar6num3;
					Name7[chara].GetCnt++;
				}
				else if (num3 > 80) {
					playSound(HitSnd);
					fill(0);
					text("☆6:", 1300, 260);
					text((let)Name6[randomstar6num3].name, 1500, 260);
					chara = randomstar6num3;
					Name6[chara].GetCnt++;
				}
				else if (num3 > 53) {
					fill(0);
					text("☆5:", 1300, 260);
					text((let)Name5[randomstar5num3].name, 1500, 260);
					chara = randomstar5num3;
					Name5[chara].GetCnt++;
				}
				else {
					fill(0);
					text("☆4:", 1300, 260);
					text((let)Name4[randomstar4num3].name, 1500, 260);
					chara = randomstar4num3;
					Name4[chara].GetCnt++;
				}
			}
			//4
			if (isTrigger(KEY_F)) {
				Takara2_4Img = loadImage("..\\main\\assets\\game05\\white.png"); 
				image(Takara2_4Img, 320, 420);
				gachaCnt++;
				playSound(OpenSnd);
				if (num4 > 94) {
					playSound(AtariSnd);
					fill(213, 202, 112);
					text("★6:", 10, 460);
					fill(0);
					text((let)Name7[randomsstar6num4].name, 200, 460);
					chara = randomsstar6num4;
					Name7[chara].GetCnt++;
				}
				else if (num4 > 80) {
					playSound(HitSnd);
					fill(0);
					text("☆6:", 10, 460);
					text((let)Name6[randomstar6num4].name, 200, 460);
					chara = randomstar6num4;
					Name6[chara].GetCnt++;
				}
				else if (num4 > 53) {
					fill(0);
					text("☆5:", 10, 460);
					text((let)Name5[randomstar5num4].name, 200, 460);
					chara = randomstar5num4;
					Name5[chara].GetCnt++;
				}
				else {
					fill(0);
					text("☆4:", 10, 460);
					text((let)Name4[randomstar4num4].name, 200, 460);
					chara = randomstar4num4;
					Name4[chara].GetCnt++;
				}
			}
			//5
			if (isTrigger(KEY_G)) {
				Takara2_5Img = loadImage("..\\main\\assets\\game05\\white.png");
				image(Takara2_5Img, 970, 420);
				gachaCnt++;
				playSound(OpenSnd);
				if (num5 > 94) {
					playSound(AtariSnd);
					fill(213, 202, 112);
					text("★6:", 650, 460);
					fill(0);
					text((let)Name7[randomsstar6num5].name, 850, 460);
					chara = randomsstar6num5;
					Name7[chara].GetCnt++;
				}
				else if (num5 > 80) {
					playSound(HitSnd);
					fill(0);
					text("☆6:", 650, 460);
					text((let)Name6[randomstar6num5].name, 850, 460);
					chara = randomstar6num5;
					Name6[chara].GetCnt++;
				}
				else if (num5 > 53) {
					fill(0);
					text("☆5:", 650, 460);
					text((let)Name5[randomstar5num5].name, 850, 460);
					chara = randomstar5num5;
					Name5[chara].GetCnt++;
				}
				else {
					fill(0);
					text("☆4:", 650, 460);
					text((let)Name4[randomstar4num5].name, 850, 460);
					chara = randomstar4num5;
					Name4[chara].GetCnt++;
				}
			}
			//6
			if (isTrigger(KEY_H)) {
				Takara2_6Img = loadImage("..\\main\\assets\\game05\\white.png");
				image(Takara2_6Img, 1620, 420);
				gachaCnt++;
				playSound(OpenSnd);
				if (num6 > 94) {
					playSound(AtariSnd);
					fill(213, 202, 112);
					text("★6:", 1300, 460);
					fill(0);
					text((let)Name7[randomsstar6num6].name, 1500, 460);
					chara = randomsstar6num6;
					Name7[chara].GetCnt++;
				}
				else if (num6 > 80) {
					playSound(HitSnd);
					fill(0);
					text("☆6:", 1300, 460);
					text((let)Name6[randomstar6num6].name, 1500, 460);
					chara = randomstar6num6;
					Name6[chara].GetCnt++;
				}
				else if (num6 > 53) {
					fill(0);
					text("☆5:", 1300, 460);
					text((let)Name5[randomstar5num6].name, 1500, 460);
					chara = randomstar5num6;
					Name5[chara].GetCnt++;
				}
				else {
					fill(0);
					text("☆4:", 1300, 460);
					text((let)Name4[randomstar4num6].name, 1500, 460);
					chara = randomstar4num6;
					Name4[chara].GetCnt++;
				}
			}
			//7
			if (isTrigger(KEY_J)) {
				Takara2_7Img = loadImage("..\\main\\assets\\game05\\white.png");
				image(Takara2_7Img, 320, 620);
				gachaCnt++;
				playSound(OpenSnd);
				if (num7 > 94) {
					playSound(AtariSnd);
					fill(213, 202, 112);
					text("★6:", 10, 660);
					fill(0);
					text((let)Name6[randomsstar6num7].name, 200, 660);
					chara = randomsstar6num7;
					Name7[chara].GetCnt++;
				}
				else if (num7 > 80) {
					playSound(HitSnd);
					fill(0);
					text("☆6:", 10, 660);
					text((let)Name6[randomstar6num7].name, 200, 660);
					chara = randomstar6num7; 
					Name6[chara].GetCnt++;
				}
				else if (num7 > 53) {
					fill(0);
					text("☆5:", 10, 660);
					text((let)Name5[randomstar5num7].name, 200, 660);
					chara = randomstar5num7; 
					Name5[chara].GetCnt++;
				}
				else {
					fill(0);
					text("☆4:", 10, 660);
					text((let)Name4[randomstar4num7].name, 200, 660);
					chara = randomstar4num7; 
					Name4[chara].GetCnt++;
				}
			}
			//8
			if (isTrigger(KEY_K)) {
				Takara2_8Img = loadImage("..\\main\\assets\\game05\\white.png");
				image(Takara2_8Img, 970, 620);
				gachaCnt++;
				playSound(OpenSnd);
				if (num8 > 94) {
					playSound(AtariSnd);
					fill(213, 202, 112);
					text("★6:", 650, 660);
					fill(0);
					text((let)Name7[randomsstar6num8].name, 850, 660);
					chara = randomsstar6num8;
					Name7[chara].GetCnt++;
				}
				else if (num8 > 80) {
					playSound(HitSnd);
					fill(0);
					text("☆6:", 650, 660);
					text((let)Name6[randomstar6num8].name, 850, 660);
					chara = randomstar6num8;
					Name6[chara].GetCnt++;
				}
				else if (num8 > 53) {
					fill(0);
					text("☆5:", 650, 660);
					text((let)Name5[randomstar5num8].name, 850, 660);
					chara = randomstar5num8;
					Name5[chara].GetCnt++;
				}
				else {
					fill(0);
					text("☆4:", 650, 660);
					text((let)Name4[randomstar4num8].name, 850, 660);
					chara = randomstar4num8;
					Name4[chara].GetCnt++;
				}
			}
			//9
			if (isTrigger(KEY_L)) {
				Takara2_9Img = loadImage("..\\main\\assets\\game05\\white.png");
				image(Takara2_9Img, 1620, 620);
				gachaCnt++;
				playSound(OpenSnd);
				if (num9 > 94) {
					playSound(AtariSnd);
					fill(213, 202, 112);
					text("★6:", 1300, 660);
					fill(0);
					text((let)Name7[randomsstar6num9].name, 1500, 660);
					chara = randomsstar6num9;
					Name7[chara].GetCnt++;
				}
				else if (num9 > 80) {
					playSound(HitSnd);
					fill(0);
					text("☆6:", 1300, 660);
					text((let)Name6[randomstar6num9].name, 1500, 660);
					chara = randomstar6num9;
					Name6[chara].GetCnt++;
				}
				else if (num9 > 53) {
					fill(0);
					text("☆5:", 1300, 660);
					text((let)Name5[randomstar5num9].name, 1500, 660);
					chara = randomstar5num9;
					Name5[chara].GetCnt++;
				}
				else {
					fill(0);
					text("☆4:", 1300, 660);
					text((let)Name4[randomstar4num9].name, 1500, 660);
					chara = randomstar4num9;
					Name4[chara].GetCnt++;
				}
			}
			//10
			if (isTrigger(KEY_P)) {
				Takara2_10Img = loadImage("..\\main\\assets\\game05\\white.png");
				image(Takara2_10Img, 970, 820);
				gachaCnt++;
				playSound(OpenSnd);
				if (num10 > 94) {
					playSound(AtariSnd);
					fill(213, 202, 112);
					text("★6:", 650, 860);
					fill(0);
					text((let)Name7[randomsstar6num10].name, 850, 860);
					chara = randomsstar6num10;
					Name7[chara].GetCnt++;
				}
				else if (num10 > 80) {
					playSound(HitSnd);
					fill(0);
					text("☆6:", 650, 860);
					text((let)Name6[randomstar6num10].name, 850, 860);
					chara = randomstar6num10; 
					Name6[chara].GetCnt++;
				}
				else if (num10 > 53) {
					fill(0);
					text("☆5:", 650, 860);
					text((let)Name5[randomstar5num10].name, 850, 860);
					chara = randomstar5num10;
					Name5[chara].GetCnt++;
				}
				else {
					fill(0);
					text("☆4:", 650, 860);
					text((let)Name4[randomstar4num10].name, 850, 860);
					chara = randomstar4num10;
					Name4[chara].GetCnt++;
				}
			}
		}
		FreamCount -= 15;
		if (FreamCount == 0) {
			Takara2_1Img = loadImage("..\\main\\assets\\game05\\takarabako2.png");
			Takara2_2Img = loadImage("..\\main\\assets\\game05\\takarabako2.png");
			Takara2_3Img = loadImage("..\\main\\assets\\game05\\takarabako2.png");
			Takara2_4Img = loadImage("..\\main\\assets\\game05\\takarabako2.png");
			Takara2_5Img = loadImage("..\\main\\assets\\game05\\takarabako2.png");
			Takara2_6Img = loadImage("..\\main\\assets\\game05\\takarabako2.png");
			Takara2_7Img = loadImage("..\\main\\assets\\game05\\takarabako2.png");
			Takara2_8Img = loadImage("..\\main\\assets\\game05\\takarabako2.png");
			Takara2_9Img = loadImage("..\\main\\assets\\game05\\takarabako2.png");
			Takara2_10Img = loadImage("..\\main\\assets\\game05\\takarabako2.png");
			State = GACHA;
		}
	}

	int GAME::collision() {
		if (EHp > 0) {
			float cRight = PPx + PhalfW;
			float cLeft = PPx - PhalfW;
			float cTop = PPy - PhalfH;
			float cBottom = PPy + PhalfH;

			float eRight = EPx + EhalfW;
			float eLeft = EPx - EhalfW;
			float eTop = EPy - EhalfH;
			float eBottom = EPy + EhalfH;

			if (cRight < eLeft || eRight < cLeft ||
				eBottom < cTop || cBottom < eTop) {
				return 0;
			}
			else {
				return 1;
			}
		}
		return 0;
	}

	int GAME::collision2() {
		if (PBHp > 0) {
			float PbRight = PBPx + PBhalfW;
			float PbLeft = PBPx - PBhalfW;
			float PbTop = PBPy - PBhalfH;
			float PbBottom = PBPy + PBhalfH;

			float eRight = EPx + EhalfW;
			float eLeft = EPx - EhalfW;
			float eTop = EPy - EhalfH;
			float eBottom = EPy + EhalfH;

			if (PbRight < eLeft || eRight < PbLeft ||
				eBottom < PbTop || PbBottom < eTop) {
				return 0;
			}
			else {
				return 1;
			}
		}
		return 0;
	}

	int GAME::collision3() {
		if (EBHp > 0) {
			float EbRight = EBPx + EBhalfW;
			float EbLeft = EBPx - EBhalfW;
			float EbTop = EBPy - EBhalfH;
			float EbBottom = EBPy + EBhalfH;

			float lRight = Px + halfW;
			float lLeft = Px - halfW;
			float lTop = Py - halfH;
			float lBottom = Py + halfH;

			if (EbRight < lLeft || lRight < EbLeft ||
				lBottom < EbTop || EbBottom < lTop) {
				return 0;
			}
			else {
				return 1;
			}
		}
		return 0;
	}

	void GAME::hpGauge() {
		strokeWeight(0);
		fill(128);
		rectMode(CORNER);
		rect(500, EHpY + hpGaugeOfsY, EMaxHp * 2, hpGaugeWidth);
		if (EHP > EHpWarning) {
			fill(0, 255, 0);
		}
		else if (EHP > EHpDenger) {
			fill(255, 255, 0);
		}
		else {
			fill(255, 0, 0);
		}
		rect(500, EHpY + hpGaugeOfsY, EHP * 2, hpGaugeWidth);
		rectMode(CENTER);

		textSize(50);
		fill(0);
		text((let)EHP, EHpX, 120);
	}

	void GAME::hpGauge2() {
		strokeWeight(0);
		fill(128);
		rectMode(CORNER);
		rect(HpX, HpY, MaxHp * 10, hpGaugeWidth);
		if (HP > HpWarning) {
			fill(0, 255, 0);
		}
		else if (HP > HpDenger) {
			fill(255, 255, 0);
		}
		else {
			fill(255, 0, 0);
		}
		rect(HpX, HpY, HP * 10, hpGaugeWidth);
		rectMode(CENTER);

		textSize(50);
		fill(0);
		text((let)HP, 1630, 1070);
	}

	void GAME::draw() {
		clear();
		rectMode(CORNER);
		image(BackImg, 0, 0);

		strokeWeight(15);
		stroke(255, 0, 0);
		line(GPRx, 0, GPRx, GPRy);

		strokeWeight(15);
		stroke(255, 255, 0);
		line(GPYx, 0, GPYx, GPYy);

		strokeWeight(15);
		stroke(0, 255, 255);
		line(GPBx, 0, GPBx, GPBy);

		strokeWeight(15);
		stroke(0, 180, 0);
		line(GPGx, 0, GPGx, GPGy);

		rectMode(CENTER);
		image(KizaruImg, PPx, PPy);
		image(EnelImg, EPx, EPy);

		fill(255, 0, 0);
		textSize(75);
		text((let)GPR + "Pt", 90, 1080);

		fill(255, 255, 0);
		textSize(75);
		text((let)GPY + "Pt", 500, 1080);

		fill(0, 255, 255);
		textSize(75);
		text((let)GPB + "Pt", 880, 1080);

		fill(0, 180, 0);
		textSize(75);
		text((let)GPG + "Pt", 1280, 1080);

		fill(255, 0, 255);
		textSize(75);
		text((let)GPP + "Pt", 1670, 1080);

		fill(0);
		textSize(100);
		text((let)Point + "Pt", 0, 100);

		fill(255, 0, 50);
		textSize(100);
		text((let)ClearPoint + "Pt", 0, 200);


		if (StageCount == 3) {
			textSize(100);
			fill(0);
			text("Last", 0, 400);
		}
		else {
			textSize(100);
			fill(0);
			text((let)StageCount, 0, 400);
		}

		//当たり判定エリア
		fill(255, 255, 255, 128);
		rect(PPx, PPy, PhalfW * 1.5f, PhalfH * 1.5f);
		rect(EPx, EPy, EhalfW * 1.5f, EhalfH * 1.5f);
	}

	void GAME::draw2() {
		clear();
		rectMode(CORNER);
		image(BackImg, 0, 0);

		rectMode(CENTER);
		image(EnelImg, EPx, EPy);

		rectMode(CENTER);
		image(LuffyImg, Px, Py);

		fill(255);
		if (PBHp > 0) {
			image(PunchImg, PBPx, PBPy);
		}

		if (EBHp > 0) {
			image(TamaImg, EBPx, EBPy);
		}

		if (collision2()) {
			image(HitImg, PBPx, PBPy);
		}

		hpGauge();

		hpGauge2();

		//当たり判定エリア
		fill(255, 255, 255, 128);
		rect(Px, Py, halfW, halfH);
		rect(EPx, EPy, EhalfW * 2.0f, EhalfH * 2.0f);
	}
}