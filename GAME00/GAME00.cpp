#include "../../libOne/inc/libOne.h"
#include "../../libOne/inc/graphic.h"
#include "../../libOne/inc/sound.h"
#include "../MAIN/MAIN.h"
#include "GAME00.h"
namespace GAME00
{
	int GAME::create()
	{
		State = TITLE;
		Player.create();
		for (int i = 0; i < Enum; i++) {
			Enemies[i].create();
		}
		Object.create();
		for (int i = 0; i < Obj2_Max; i++) {
			Object2[i].create();
		}
		Flag.create();
		StartWorldY = Player.top();
		BackGroundImg = loadImage("../main/assets/game00/back.png");;
		HpImg = loadImage("../main/assets/game00/heart.png");
		EmptyHpImg = loadImage("../main/assets/game00/heart_empty.png");
		Bgm = loadSound("../main/assets/game00/bgm.wav");
		GameOverSe = loadSound("../main/assets/game00/game_over.wav");
		PushSe = loadSound("../main/assets/game00/push.wav");
		GetSe = loadSound("../main/assets/game00/get.wav");
		return 0;
	}

	void GAME::Title()
	{
		showCursor();

		clear(0, 0, 128);

		fill(255);
		textSize(120);
		text("Climb Higher", 600, 250);
		textSize(75);
		text("移動：A⇔D",200,800);
		text("ジャンプ：SPACE", 200, 900);
		text("2段ジャンプ：SPACE2回",200,1000);
		text("リセット：R", 1200, 850);
		textSize(50);
		text("PLAYを押してスタート", 720, 630);

		fill(255);
		textSize(50);
		text("ENTERキーでメニューに戻る", 0,1080);

		int Pbx = 760;
		int Pby = 400;
		int Pbw = 400;
		int Pbh = 120;

		if (isMouseOnPlay(Pbx, Pby, Pbw, Pbh))
			fill(255, 200, 0);
		else
			fill(255);

		rect(Pbx,Pby,Pbw,Pbh);

		fill(0);
		textSize(60);
		text("PLAY", Pbx + 130, Pby + 80);

		if(isMouseOnPlay(Pbx,Pby,Pbw,Pbh) && isTrigger(MOUSE_LBUTTON)){
			setVolume(Bgm, -4300);
			playLoopSound(Bgm);
			setVolume(PushSe, -3000);
			playSound(PushSe);
			Player.init();
			Player.saveStartPos();

			FallCount = 0;

			EnemiesInit();
			Object.init();

			Object2Init();
			Flag.init();

			//制限時間
			TimeInit();
			State = PLAY;
		}
	}

	void GAME::Play()
	{
		hideCursor();
		image(BackGroundImg, 0, 0);
		Player.update();
		for (int i = 0; i < Enum; i++) {
			Enemies[i].update();
		}

		TimeLimit -= delta;

		for (int i = 0; i < Obj2_Max; i++) {
			Object2[i].update();
		}

		Player.landOn(Object);

		for (int i = 0; i < Obj2_Max; i++) {
			Player.hitCeiling(Object2[i]);
			Player.hitSide(Object2[i]);
			bool onFloor = Player.landOn(Object2[i]);

			//落下処理
			if ((i == 3 || i == 4 || i == 13 || i == 17 ||
				i == 18 || i == 19 || i == 20 || i == 21 ||
				i == 27 || i == 28) && onFloor) {
				Object2[i].startfall();
			}

			//移動床処理
			if (i == 10 || i == 14) {
				Object2[i].startmove();
			}
		}

		const float SCROLL_LINE = height / 2;

		float diff = (SCROLL_LINE - Player.top()) * 0.1f;

		const float SCROLL_DOWN_LINE = SCROLL_LINE + 200;

		if (Player.top() < SCROLL_LINE) {

			float move = SCROLL_LINE - Player.top();

			Player.moveY(move);
			for (int i = 0; i < Enum; i++) {
				Enemies[i].moveY(move);
				Enemies[i].moveBulletY(move);
			}
			Object.moveY(move);

			for (int i = 0; i < Obj2_Max; i++) {
				Object2[i].moveY(move);
			}

			WorldScrollY += move;

			if (WorldScrollY < 0)
				WorldScrollY = 0;
		}

		if (Player.top() > SCROLL_DOWN_LINE) {

			float move = diff;

			if (Object.bottom() > 0) {

				Player.moveY(move);
				for (int i = 0; i < Enum; i++) {
					Enemies[i].moveY(move);
					Enemies[i].moveBulletY(move);
				}
				Object.moveY(move);

				for (int i = 0; i < Obj2_Max; i++) {
					Object2[i].moveY(move);
				}

				WorldScrollY += move;
			}

			if (WorldScrollY < 0)
				WorldScrollY = 0;
		}
		if (Player.top() > height) {
			FallCount++;
			Player.damage(1);
			Player.respawn();

			EnemiesInit();
			Object.init();
			Object2Init();

			WorldScrollY = 0;
		}

		Player.draw();
		Object.draw();

		for (int i = 0; i < Obj2_Max; i++) {
			Object2[i].draw();
		}

		for (int i = 0; i < Enum; i++) {
			Enemies[i].draw();
		}

		Flag.draw(WorldScrollY);

		for (int i = 0; i < Enum; i++) {
			if (Player.hit(Enemies[i])) {
				Player.damage(1);
			}
		}

		for (int e = 0; e < Enum; e++) {
			for (int b = 0; b < 10; b++) {
				BULLET& bullet = Enemies[e].getbullet(b);
				if (Player.hit(Enemies[e].getbullet(b))) {
					Player.damage(1);
					bullet.deactivate();
				}
			}
		}

		if (Player.right() > Flag.left() &&
			Player.left() < Flag.right() &&
			Player.bottom() > Flag.top(WorldScrollY) &&
			Player.top() < Flag.bottom(WorldScrollY)) {
			ClearTime = 80.0f - TimeLimit;
			setVolume(GetSe, -3000);
			playSound(GetSe);
			State = CLEAR;
			stopSound(Bgm);
		}
		if (TimeLimit <= 0 || Player.isDead()) {
			stopSound(Bgm);
			setVolume(GameOverSe, -3200);
			playSound(GameOverSe);
			State = GAMEOVER;
		}
		if (isTrigger(KEY_R)) {
			ResetGame();
			TimeInit();
		}

		textSize(30);
		fill(0);
		text("  TIME :", 30, 80);
		text((int)TimeLimit, 200, 80);

		float currentHeight = WorldScrollY;

		textSize(30);
		fill(0);
		text("HEIGHT :", 30, 30);
		text((int)currentHeight, 200, 30);

		textSize(30);
		fill(0);
		text("    HP :", 30, 130);
		for (int i = 0; i < 7; i++) {
			if (i < Player.getHp()) {
				image(HpImg, 150 + i * 35, 100);
			}
			else {
				image(EmptyHpImg, 150 + i * 35, 100);
			}
		}
		//----------------------------------------------------------------------
		//デバッグ用
		/*
		for (int i = 0; i < Obj2_Max; i++) {
			Object2[i].draw();
			Object2[i].drawDebugNum(i);
		}
		*/
//----------------------------------------------------------------------

	}

	void GAME::Clear() {
		showCursor();
		clear(0, 0, 128);
		fill(255, 255, 0);
		textSize(120);
		text("GAME CLEAR", 675, 250);

		fill(255);
		textSize(80);

		text("落ちた回数   :", 700, 750);
		text(FallCount, 1300, 750);

		text("クリアタイム :", 700, 900);
		text((int)ClearTime, 1300, 900);
		fill(255);
		textSize(50);
		text("ENTERキーでメニューに戻る", 0, 1080);

		int Pbx = 760;
		int Pby = 450;
		int Pbw = 400;
		int Pbh = 120;

		if (isMouseOnPlay(Pbx, Pby, Pbw, Pbh))
			fill(255, 200, 0);
		else
			fill(255);

		rect(Pbx, Pby, Pbw, Pbh);

		fill(0);
		textSize(60);
		text("TITLE", Pbx + 100, Pby + 80);

		if (isMouseOnPlay(Pbx,Pby,Pbw,Pbh) && isTrigger(MOUSE_LBUTTON)) {
			setVolume(PushSe, -3000);
			playSound(PushSe);
			State = TITLE;
			ResetGame();
		}
	}
	void GAME::GameOver()
	{
		showCursor();
		clear(128, 0, 0);
		fill(255);
		textSize(120);
		text("GAME OVER", 700, 250);
		fill(255);
		textSize(50);
		text("ENTERキーでメニューに戻る", 0, 1080);

		int Pbx = 760;
		int Pby = 450;
		int Pbw = 400;
		int Pbh = 120;

		if (isMouseOnPlay(Pbx, Pby, Pbw, Pbh))
			fill(255, 200, 0);
		else
			fill(255);

		rect(Pbx, Pby, Pbw, Pbh);

		fill(0);
		textSize(60);
		text("REPLAY", Pbx + 100, Pby + 80);

		if (isMouseOnPlay(Pbx, Pby, Pbw, Pbh) && isTrigger(MOUSE_LBUTTON)) {
			setVolume(PushSe, -3000);
			playSound(PushSe);
			State = PLAY;
			RePlay();
		}
	}

	void GAME::ResetGame()
	{
		Player.init();
		EnemiesInit();
		Object.init();

		Object2Init();

		WorldScrollY = 0;

		TimeLimit -= 3.0f;
	}

	void GAME::RePlay()
	{
		setVolume(Bgm, -4300);
		playLoopSound(Bgm);
		Player.init();
		FallCount = 0;
		EnemiesInit();
		Object.init();

		Object2Init();

		WorldScrollY = 0;

		TimeInit();
	}

	void GAME::destroy()
	{
		Player.destroy();
		stopSound(Bgm);

		releaseSound(Bgm);
		releaseSound(PushSe);
		releaseSound(GetSe);
		releaseSound(GameOverSe);
	}

	void GAME::proc()
	{
		clear(0, 0, 64);
		textSize(50);
		fill(255, 255, 0);
		text("GAME00", 0, 100);
		
		if (isTrigger(KEY_ENTER)) {
			main()->backToMenu();
		}
		if (State == TITLE)
			Title();
		else if (State == PLAY)
			Play();
		else if (State == GAMEOVER)
			GameOver();
		else if (State == CLEAR)
			Clear();
	}

	bool GAME::isMouseOnPlay(int x,int y,int w,int h) {
		return mouseX >= x &&
			mouseX <= x + w &&
			mouseY >= y &&
			mouseY <= y + h;
	}
	
	void GAME::Object2Init() {
		Object2[0].init(350, 1050, false, false);
		Object2[1].init(650, 880, false, false);
		Object2[2].init(960, 750, false, false);
		Object2[3].init(1320, 650, true, false);
		Object2[4].init(1695, 550, true, false);
		Object2[5].init(900,500,false,false);
		Object2[6].init(1300,350,false,false);
		Object2[7].init(650,250,false,false);
		Object2[8].init(350,100,false,false);
		Object2[9].init(50,0,false,false);
		Object2[10].init(500,-250,false,true);
		Object2[11].init(950,-500,false,false);
		Object2[12].init(1450,-750,false,false);
		Object2[13].init(1100,-1000,true,false);
		Object2[14].init(900,-1100,false,true);
		Object2[15].init(350,-1300,false,false);
		Object2[16].init(650,-1600,false,false);
		Object2[17].init(850,-1750,true,false);
		Object2[18].init(1050,-1900,true,false);
		Object2[19].init(1250,-2050,true,false);
		Object2[20].init(1450, -2200, true, false);
		Object2[21].init(1650, -2350, true, false);
		Object2[22].init(1350, -2600, false, false);
		Object2[23].init(1050, -2900, false, false);
		Object2[24].init(850, -3200, false, false);
		Object2[25].init(835, -3500, false, false);
		Object2[26].init(815, -3800, false, false);
		Object2[27].init(550, -4000, true, false);
		Object2[28].init(200, -4200, true, false);
		Object2[29].init(-100, -4450, false, false);
	}

	void GAME::EnemiesInit() {
		Enemies[0].init(0.0f, 0.0f);
		Enemies[1].init(145, -750); 
		Enemies[2].init(1050, -2900);
	}

	void GAME::TimeInit() {
		TimeLimit = 80.0f;
	}
}