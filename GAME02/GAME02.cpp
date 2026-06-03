#include "../../libOne/inc/graphic.h"
#include "../../libOne/inc/input.h"
#include "../../libOne/inc/framework.h"
#include "../../libOne/inc/window.h"
#include "../../libOne/inc/mathUtil.h"
#include "../MAIN/MAIN.h"
#include "GAME02.h"
#include <crtdbg.h>
//ネストの深い場所{}のライン合わせてます
// 
//Next 敵のディレイをrandにする
namespace GAME02
{
	void GAME::Init() {
		ShotDelay = 0;
		Wave = 5;
		Score = 0;
		Delay = 10;
		Hdelay = 20;
		Deg = 0;
	}
	//全滅判定
	bool GAME::AllDead() {
		for (int i = 0; i < ENEMY_NUM; i++) {
			if (Enemy[i].Alive) {
				return false;
			}
		}
		return true;
	}
	void GAME::Bossshot() {
		if (Boss.Delay <= 0)
		{
			static float offset = 0;
			for (int i = 0; i < 32; i++) {
				float angle = (360.0f / 32.0f) * i + offset;
				Deg = angle;
				Deg += 1;
				float Vx = Sin(Deg) * 2;
				float Vy = -Cos(Deg) * 2;
				for (int j = 0; j < BULLET_BNUM; j++)
				{
					if (!Bbullet[j].Alive)
					{
						Bbullet[j].set(Boss.Px, Boss.Py, Vx, Vy);
						offset += 1;
						break;
					}

				}
			}
			Boss.Delay = 20;
		}
		Boss.Delay--;
	}
	
	int GAME::create()
	{
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		State = TITLE;

		Player.create();
		Boss.create();
		Background.create();
		for (int i = 0; i < ITEM_NUM; i++) {
			Item[i].create();
		}
		for (int i = 0; i < BULLET_NUM; i++) {
			Bullet[i].create();
		}
		for (int i = 0; i < BULLET_ENUM; i++) {
			Ebullet[i].create();
		}
		for (int i = 0; i < ENEMY_NUM; i++) {
			Enemy[i].create();
		}
		for (int i = 0; i < SHOT_POINT; i++) {
			Shotpoint[i].create();
		}
		for (int i = 0; i < BULLET_BNUM; i++) {
			Bbullet[i].create();
		}
		HighScore = Save.loadscore();
		return 0;
	}
		

	

	void GAME::Title() {
		showCursor();
		clear(255, 0, 255);
		fill(255,255,255);
		text("Title", 0, 50);
		textSize(50);
		text("PLAY", width / 2 - 50, 450);
		text("HARD?", width / 2 - 50, 550);
		text("WASD : 移動", 0, 975);
		text("SHIFTキー : 低速移動", 0, 1025);
		text("左クリック/SPACEキー : 射撃", 0, 1075);
		Init();
		Player.init();
		Boss.init();
		//初期化処理
		if (MouseX > width/2-50 && MouseX < width/2+50 && MouseY > 400 && MouseY < 450 && isTrigger(MOUSE_LBUTTON)){
			for (int i = 0; i < ITEM_NUM; i++) {
				Item[i].init();
			}
			for (int i = 0; i < BULLET_NUM; i++) {
				Bullet[i].init();
			}
			for (int i = 0; i < SHOT_POINT; i++) {
				Shotpoint[i].init();
			}
			for (int i = 0; i < BULLET_ENUM; i++) {
				Ebullet[i].init();
			}
			for (int i = 0; i < BULLET_BNUM; i++){
				Bbullet[i].init();
			}
			for (int i = 0; i < ENEMY_NUM; i++)
			{
				bool retry;
				do
				{
					retry = false;
					Enemy[i].init();

					for (int j = 0; j < i; j++)
					{
						if (Enemy[i].hit(Enemy[j]))
						{
							retry = true;
							break;
						}
					}
				} while (retry);
			}
			State = PLAY;
		}
		if (MouseX > width / 2 - 50 && MouseX < width / 2 + 65 && MouseY > 500 && MouseY < 550 && isTrigger(MOUSE_LBUTTON)) 
		{
			for (int i = 0; i < ITEM_NUM; i++) {
				Item[i].init();
			}
			for (int i = 0; i < BULLET_NUM; i++) {
				Bullet[i].init();
			}
			for (int i = 0; i < SHOT_POINT; i++) {
				Shotpoint[i].init();
			}
			for (int i = 0; i < BULLET_ENUM; i++) {
				Ebullet[i].init();
			}
			for (int i = 0; i < BULLET_BNUM; i++)
			{
				Bbullet[i].init();
			}
			for (int i = 0; i < ENEMY_NUM; i++)
			{
				bool retry;
				do
				{
					retry = false;
					Enemy[i].init();

					for (int j = 0; j < i; j++)
					{
						if (Enemy[i].hit(Enemy[j]))
						{
							retry = true;
							break;
						}
					}
				} while (retry);
			}
			State = SIBARI;
		}
	}
	//メインループ
	void GAME::Play() {
		clear(20, 255, 255);
		hideCursor();
		HighScore = Save.loadscore();
		//更新と表示
		Background.draw();
		Player.update();
		Player.draw();
		
		
		text((let)"Score " +Score, 0, 50);
		text((let)"HighScore " + HighScore, 0, 100);
		text((let)"Delay " + ShotDelay, 0, 150);
		text((let)"BossHp " + Boss.Hp, 0, 200);
		text((let)"Wave" + Wave, 0, 250);
		text((let)"Limit" + Boss.LimitTime, 0, 300);

		for (int i = 0; i < BULLET_NUM; i++) {
			Bullet[i].update();
			Bullet[i].draw();
		}
		for (int i = 0; i < SHOT_POINT; i++) {
			Shotpoint[i].draw();
		}
		for (int i = 0; i < BULLET_ENUM; i++) {
			Ebullet[i].update();
			Ebullet[i].draw();
		}
		for (int i = 0; i < BULLET_BNUM; i++) {
			Bbullet[i].update();
			Bbullet[i].draw();
		}
		for (int i = 0; i < ITEM_NUM; i++) {
			Item[i].update();
			Item[i].draw();
		}
		for (int i = 0; i < ENEMY_NUM; i++) {
			if (!Enemy[i].Alive) {
				continue;
			}
			Enemy[i].update();
			Enemy[i].draw();
		}
	

		//弾処理
		ShotCount = 0;
		ShotPoint = 0;
		
		if (ShotDelay > 0) {
			ShotDelay--;
		}
		if (ShotDelay <= 0) {
			for (int i = 0; i < BULLET_NUM; i++)
			{
				if (!Bullet[i].Alive) 
				{
					if (isPress(KEY_SPACE)||isPress(MOUSE_LBUTTON))
					{
						Bullet[i].shoot(Player.Px+offsetx[ShotCount], Player.Py + offsety[ShotCount]);
						ShotCount++;
						if (ShotCount>=Player.Shotlevel) {
							ShotDelay = Delay;
							break;
						}
					}
				}
			}
		}
		for (int e = 0; e < ENEMY_NUM; e++) 
		{
			if (!Enemy[e].Alive) continue;

			if (Enemy[e].Delay <= 0) 
			{
				for (int i = 0; i < BULLET_ENUM; i++)
				{
					if (!Ebullet[i].Alive)
					{
						Ebullet[i].shoot(Enemy[e].Px, Enemy[e].Py);
						Enemy[e].Delay = rand() % 30 + 30;
						break;

					}
				}
			}
			Enemy[e].Delay--;
		}
		for (int i = 0; i < SHOT_POINT; i++) {
			Shotpoint[i].setPosition(Player.Px + offsetx[ShotPoint], Player.Py + offsety[ShotPoint]);
			ShotPoint++;
			if (ShotPoint >= Player.Shotlevel) {
				break;
			}
		}

		if (Player.Bom > 0 && isTrigger(KEY_B)) {
			for (int i = 0; i < BULLET_ENUM; i++) {
				Ebullet[i].Alive = false;
			}
		}
		
		//当たったら～{
		for (int b = 0; b < BULLET_NUM; b++) 
		{
			if (!Bullet[b].Alive) 
			{
				continue;
			}
			for (int e = 0; e < ENEMY_NUM; e++)
			{
				if (!Enemy[e].Alive)
				{
					continue;
				}
					if (Bullet[b].hit(Enemy[e]))
					{
						Enemy[e].Hp--;
						if (Enemy[e].Hp == 0)
						{
							Enemy[e].Alive = false;
							Score += 100;
							if (Enemy[e].drop())
							{
								for (int i = 0; i < ITEM_NUM; i++)
								{
									if (!Item[i].Alive)
									{
										Item[i].set(Enemy[e].Px, Enemy[e].Py);
										break;
									}
								}
							}
						}
						Bullet[b].Alive = false;
						ShotCount--;
				
					}

			}
		}
		for (int i = 0; i < ENEMY_NUM; i++) {
			if (Enemy[i].Alive) {
				if (Player.hit(Enemy[i])) {
					Save.savescore(Score);
					State = GAMEOVER;
				}
			}
		}
		for (int i = 0; i < BULLET_ENUM;i++) {
			if (Ebullet[i].Alive) {
				if (Ebullet[i].hit(Player)) {
					Save.savescore(Score);
					State = GAMEOVER;
				}
			}
		}
		
		for (int i = 0; i < ITEM_NUM; i++) {
			if (Item[i].Alive) {
				if (Item[i].hit(Player)) {
					Item[i].Alive = false;
					if (Player.Shotlevel < 4) {
						Player.Shotlevel++;
					}
					else if (Player.Shotlevel >= 4 && ShotDelay > 1) {
						Delay -= 0.5f;
					}
				}
			}
		}
		for (int i = 0; i < BULLET_BNUM; i++) {
			if (Bbullet[i].Alive) {
				if (Bbullet[i].hit(Player)) {
					Save.savescore(Score);
					State = GAMEOVER;
				}
			}
		}
		for (int i = 0; i < BULLET_NUM; i++) {
			if (Bullet[i].Alive) {
				if (Boss.hit(Bullet[i])) {
					Bullet[i].Alive = false;
				}
			}
		}
	    //}
		//ウェーブ
		if (Wave > 0) {
			if (AllDead()) {
				Wave -= 1;
				for (int i = 0; i < ENEMY_NUM; i++)
				{
					if (Wave == 0) {
						break;
					}
					bool retry;
					do
					{
						retry = false;
						Enemy[i].init();

						for (int j = 0; j < i; j++)
						{
							if (Enemy[i].hit(Enemy[j]))
							{
								retry = true;
								break;
							}
						}
					} while (retry);
					Enemy[i].Hp += 5;
					if (Enemy[i].Delay > 10) {
						Enemy[i].Delay -= 2;
					}
				}

			}
		}
	
		
		
		if (Wave == 0) {
			//敵の弾消してからボス召喚
			for (int i = 0; i < BULLET_ENUM; i++) {
				Ebullet[i].Alive = false;
			}
			Boss.update();
			Boss.draw();
			if (Boss.Cnt4 < 0) {
				Bossshot();
			}
			
		}
		if (Boss.Hp <= 0) {
			Save.savescore(Score);
			State = CLEAR;
		}
		//スコア保存
		
	}
	void GAME::Sibarimode() {
		clear(20, 255, 255);
		hideCursor();
		HighScore = Save.loadscore();
		//更新と表示
		Background.draw();
		Player.sibariupdate();
		Player.draw();
		text((let)"Score " + Score, 0, 50);
		text((let)"HighScore " + HighScore, 0, 100);
		text((let)"Delay " + ShotDelay, 0, 150);
		
		for (int i = 0; i < BULLET_NUM; i++) {
			Bullet[i].update();
			Bullet[i].draw();
		}
		for (int i = 0; i < SHOT_POINT; i++) {
			Shotpoint[i].draw();
		}
		for (int i = 0; i < BULLET_ENUM; i++) {
			Ebullet[i].update();
			Ebullet[i].draw();
		}
		for (int i = 0; i < ITEM_NUM; i++) {
			Item[i].update();
			Item[i].draw();
		}
		for (int i = 0; i < ENEMY_NUM; i++) {
			if (!Enemy[i].Alive) {
				continue;
			}
			Enemy[i].update();
			Enemy[i].draw();
		}

		//弾処理
		ShotCount = 0;
		ShotPoint = 0;
		
		if (ShotDelay > 0) {
			ShotDelay--;
		}
		if (ShotDelay <= 0) {
			for (int i = 0; i <= BULLET_NUM; i++)
			{
				if (!Bullet[i].Alive)
				{
					if (isPress(KEY_SPACE) || isPress(MOUSE_LBUTTON))
					{
						Bullet[i].shoot(Player.Px + offsetx[ShotCount], Player.Py + offsety[ShotCount]);
						ShotCount++;
						if (ShotCount >= Player.Shotlevel) {
							ShotDelay = Hdelay;
							break;
						}
					}
				}
			}
		}
		for (int e = 0; e < ENEMY_NUM; e++)
		{
			if (!Enemy[e].Alive) continue;

			if (Enemy[e].Delay <= 0)
			{
				for (int i = 0; i < BULLET_ENUM; i++)
				{
					if (!Ebullet[i].Alive)
					{
						Ebullet[i].shoot(Enemy[e].Px, Enemy[e].Py);
						Enemy[e].Delay = Delay = rand() % 25 + 50;
						break;

					}
				}
			}
			Enemy[e].Delay--;
		}
		for (int i = 0; i < SHOT_POINT; i++) {
			Shotpoint[i].setPosition(Player.Px + offsetx[ShotPoint], Player.Py + offsety[ShotPoint]);
			ShotPoint++;
			if (ShotPoint >= Player.Shotlevel) {
				break;
			}
		}
		//当たったら～{
		for (int b = 0; b < BULLET_NUM; b++)
		{
			if (!Bullet[b].Alive)
			{
				continue;
			}
			for (int e = 0; e < ENEMY_NUM; e++)
			{
				if (!Enemy[e].Alive)
				{
					continue;
				}
				if (Bullet[b].hit(Enemy[e]))
				{
					Enemy[e].Hp--;
					if (Enemy[e].Hp == 0)
					{
						Enemy[e].Alive = false;
						Score += 150;
						if (Enemy[e].sibaridrop())
						{
							for (int i = 0; i < ITEM_NUM; i++)
							{
								if (!Item[i].Alive)
								{
									Item[i].set(Enemy[e].Px, Enemy[e].Py);
									break;
								}
							}
						}
					}
					Bullet[b].Alive = false;
					ShotCount--;

				}

			}
		}
		for (int i = 0; i < ENEMY_NUM; i++) {
			if (Enemy[i].Alive) {
				if (Player.hit(Enemy[i])) {
					Save.savescore(Score);
					State = SIBARIOVER;
				}
			}
		}
		for (int i = 0; i < BULLET_ENUM; i++) {
			if (Ebullet[i].Alive) {
				if (Ebullet[i].hit(Player)) {
					Save.savescore(Score);
					State = SIBARIOVER;
				}
			}
		}

		for (int i = 0; i < ITEM_NUM; i++) {
			if (Item[i].Alive) {
				if (Item[i].hit(Player)) {
					Item[i].Alive = false;
					if (Player.Shotlevel < 4) {
						Player.Shotlevel++;
					}
					else if (Player.Shotlevel <= 4 && ShotDelay < 1) {
						ShotDelay -= 5;
					}
				}
			}
		}
		for (int i = 0; i < BULLET_BNUM; i++) {
			if (Bbullet[i].Alive) {
				if (Bbullet[i].hit(Player)) {
					Save.savescore(Score);
					State = SIBARIOVER;
				}
			}
		}
		//}
		//ウェーブ
		if (Wave > 0) {
			Wave--;
			if (AllDead()) {
				for (int i = 0; i < ENEMY_NUM; i++)
				{
					bool retry;
					do
					{
						retry = false;
						Enemy[i].init();

						for (int j = 0; j < i; j++)
						{
							if (Enemy[i].hit(Enemy[j]))
							{
								retry = true;
								break;
							}
						}
					} while (retry);
					Enemy[i].Hp += 5;
					if (Enemy[i].Delay > 10) {
						Enemy[i].Delay -= 5;
					}
				}

			}
		}
	
		if (Wave == 0) {
			//敵の弾消してからボス召喚
			for (int i = 0; i < BULLET_ENUM; i++) {
				Ebullet[i].Alive = false;
			}
			Boss.update();
			Boss.draw();
			if (Boss.Hp <= 4000) {
				Bossshot();
			}
			for (int i = 0; i < BULLET_BNUM; i++) {
				Bbullet[i].update();
				Bbullet[i].draw();
			}
		}
		if (Boss.Hp <= 0) {
			Save.savescore(Score);
			State = CLEAR;
		}
		
		//スコア保存

	}
	void GAME::GameOver() {
		clear(0,0,0);
		HighScore = Save.loadscore();
		Background.gameoverdraw();
		text((let)"Score " + Score, 0, 100);
		text((let)"HighScore " + HighScore, 0, 150);
		text("GameOver", 0, 50); textSize(50);
		text((let)"BossHp " + Boss.Hp, 0, 200);
		text((let)"Limit" + Boss.LimitTime, 0, 300);

		Player.draw();

		for (int i = 0; i < ITEM_NUM; i++) {
			Item[i].draw();
		}
		for (int i = 0; i < BULLET_NUM; i++) {
			Bullet[i].draw();
		}
		for (int i = 0; i < BULLET_ENUM; i++) {
			Ebullet[i].draw();
		}
		for (int i = 0; i < ENEMY_NUM; i++) {
			if (Enemy[i].Alive)
				Enemy[i].draw();
		}
		for (int i = 0; i < BULLET_BNUM; i++) {
			Bbullet[i].draw();
		}
		//すべて初期化してリトライ
		if (isTrigger(KEY_R)) {
			Player.init();
			Boss.init();
			for (int i = 0; i < BULLET_NUM; i++) {
				Bullet[i].init();
			}
			for (int i = 0; i < BULLET_ENUM; i++) {
				Ebullet[i].init();
			}
			for (int i = 0; i < BULLET_BNUM; i++) {
				Bbullet[i].init();
			}
			for (int i = 0; i < SHOT_POINT; i++) {
				Shotpoint[i].init();
			}
			for (int i = 0; i < ITEM_NUM; i++) {
				Item[i].init();
			}
			for (int i = 0; i < ENEMY_NUM; i++)
			{
				bool retry;
				do
				{
					retry = false;
					Enemy[i].init();

					for (int j = 0; j < i; j++)
					{
						if (Enemy[i].hit(Enemy[j]))
						{
							retry = true;
							break;
						}
					}
				} while (retry);
			}
			Init();
			State = PLAY;
			
		}
		
	}
	void GAME::SibariOver() {
		clear(255, 50, 50);
		HighScore = Save.loadscore();
		Player.draw();
		text((let)"Score " + Score, 0, 100);
		text((let)"HighScore " + HighScore, 0, 150);
		text("GameOver", 0, 50); textSize(50);
		for (int i = 0; i < ITEM_NUM; i++) {
			Item[i].draw();
		}
		for (int i = 0; i < BULLET_NUM; i++) {
			Bullet[i].draw();
		}
		for (int i = 0; i < BULLET_ENUM; i++) {
			Ebullet[i].draw();
		}
		for (int i = 0; i < ENEMY_NUM; i++) {
			if (Enemy[i].Alive) {
				Enemy[i].draw();
			}
		}
		//すべて初期化してリトライ
		if (isTrigger(KEY_R)) {
			Player.init();
			for (int i = 0; i < BULLET_NUM; i++) {
				Bullet[i].init();
			}
			for (int i = 0; i < BULLET_ENUM; i++) {
				Ebullet[i].init();
			}
			for (int i = 0; i < SHOT_POINT; i++) {
				Shotpoint[i].init();
			}
			for (int i = 0; i < ITEM_NUM; i++) {
				Item[i].init();
			}
			for (int i = 0; i < ENEMY_NUM; i++)
			{
				bool retry;
				do
				{
					retry = false;
					Enemy[i].init();

					for (int j = 0; j < i; j++)
					{
						if (Enemy[i].hit(Enemy[j]))
						{
							retry = true;
							break;
						}
					}
				} while (retry);
			}
			Init();
			State = SIBARI;

		}

	}
	void GAME::GameClear(){
		clear(0, 255, 0);
		HighScore = Save.loadscore();
		Background.cleardraw();
		rectMode(CENTER);
		fill(0,255,255);
		strokeWeight(10);
		text((let)"Score " + Score, 0, 50);
		text((let)"HighScore " + HighScore, 0, 100);
		text("GAMECLEAR", width/3, height / 3);
		text("ENTERでタイトルに戻る", width / 3, height / 2);
		if (isTrigger(KEY_ENTER)) {
			State = TITLE;
		}
		

	}


	void GAME::destroy()
	{
		
	}
	
	void GAME::proc()
	{
			//clear(255, 255, 255);
			if (isTrigger(KEY_M)) {
				main()->backToMenu();
			}
			if (State == TITLE) {
				Title();
			}
			else if (State == PLAY) {
				Play();
			}
			else if (State == SIBARI) {
				Sibarimode();
			}
			else if (State == GAMEOVER) {
				GameOver();
			}
			else if (State == CLEAR) {
				GameClear();
			}
			else if (State == SIBARIOVER) {
				SibariOver();
			}
	}
};