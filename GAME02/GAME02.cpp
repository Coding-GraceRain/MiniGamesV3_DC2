#include "../../libOne/inc/graphic.h"
#include "../../libOne/inc/input.h"
#include "../../libOne/inc/window.h"
#include "../../libOne/inc/mathUtil.h"
#include "../MAIN/MAIN.h"
#include "GAME02.h"
#include <crtdbg.h>
//ネストの深い場所{}のライン合わせてます
namespace GAME02
{
	void GAME::Init() {
		ShotDelay = 0;
		Wave = 5;
		Score = 0;
		Delay = 10;
		Hdelay = 15;
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
			if (Player.ControlMode[1] == 1) {
				static float offset = 0;
				for (int i = 0; i < 16; i++) {
					float angle = (360.0f / 16.0f) * i + offset;
					Deg = angle;
					Deg += 1;
					float Vx = Sin(Deg) * 3;
					float Vy = -Cos(Deg) * 3;
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
				Boss.Delay = 25;
				if (Boss.Hp < 2500) {
					Boss.Delay = 23;
				}
			}
			if (Player.ControlMode[1] == 2) {
				static float offset = 0;
				for (int i = 0; i < 48; i++) {
					float angle = (360.0f / 48.0f) * i + offset;
					Deg = angle;
					Deg += 1;
					float Vx = Sin(Deg) * 3;
					float Vy = -Cos(Deg) * 3;
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
				Boss.Delay = 25;
				if (Boss.Hp < 2500) {
					Boss.Delay = 23;
				}
			}
			if (State == HARD) {
				Boss.Delay = 23;
			}
			
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
		Sound.create();
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
		Background.titledraw();
		fill(0,0,0);
		text("Title", 0, 50);
		textSize(50);
		text("PLAY", width / 2 - 50, 450);
		text("HARD", width / 2 - 50, 550);
		text("OPTION", width / 2 - 50, 650);
		text("WASD/矢印キー : 移動", 2, 975);
		text("SHIFTキー : 低速移動", 0, 1020);
		text("左クリック/SPACEキー : 射撃", 0, 1075);
		text(" Mキー : メニュー画面に戻る ", 1240,50);
		text((let)"" + Player.ControlMode[0], 0, 100);
		Init();
		Player.init();
		Boss.init();
		

		if (MouseX > width / 2 - 50 && MouseX < width / 2 + 50 && MouseY > 400 && MouseY < 450) {
			fill(255, 255, 255);
			text("PLAY", width / 2 - 50, 450);
		}
	
		if (MouseX > width/2-50 && MouseX < width/2+50 && MouseY > 400 && MouseY < 450 && isTrigger(MOUSE_LBUTTON)){
			Sound.clicksound();
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
			GetCursorPos(&mouse);
			ClientToScreen(HWnd, &mouse);
			SetCursorPos(1280, 880);
			State = PLAY;
			Sound.playsound();
		}
		if (MouseX > width / 2 - 50 && MouseX < width / 2 + 65 && MouseY > 500 && MouseY < 550) {
			fill(255, 255, 255);
			text("HARD", width / 2 - 50, 550);
		}
		if (MouseX > width / 2 - 50 && MouseX < width / 2 + 65 && MouseY > 500 && MouseY < 550 && isTrigger(MOUSE_LBUTTON)) 
		{
			Sound.clicksound();
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
			ClientToScreen(HWnd, &mouse);
			SetCursorPos(1280, 880);
			State = HARD;
			Sound.playsound();
		}
		if (MouseX > width / 2 - 50 && MouseX < width / 2 + 100 && MouseY > 600 && MouseY < 650) {
			fill(255, 255, 255);
			text("OPTION", width / 2 - 50, 650);
		}
		if (MouseX > width / 2 - 50 && MouseX < width / 2 + 100 && MouseY > 600 && MouseY < 650&&isTrigger(MOUSE_LBUTTON)) {
			Sound.clicksound();
			State = OPTION;
		}
	}
	void GAME::Option() {
		clear();
		Background.titledraw();
		fill(0, 0, 0);
		text("操作をマウスにすると難易度が上がります(簡単すぎたので)", 0, 50);
		if (Choose[0] == 0) {
			text("低速移動:長押し", width / 2 - 150, 450);
			Player.ControlMode[0] = 1;
		}
		if (Choose[1] == 0) {
			text("操作モード:WASD/矢印キー", width / 2 - 150, 550);
		}
		if (Choose[2] == 0) {
			text("オーディオ:あり", 0, 1080);
		}
		if (MouseX > width / 2 - 150 && MouseX < width / 2 + 220 && MouseY > 400 && MouseY < 450 && Choose[0] == 0) {
			fill(255, 255, 255);
			text("低速移動:長押し", width / 2 - 150, 450);
		}
		if (MouseX > width / 2 - 150 && MouseX < width / 2 + 220 && MouseY > 400 && MouseY < 450 && isTrigger(MOUSE_LBUTTON)) {
			Sound.clicksound();
			Cur = 1;
			if (Choose[0] == 0)
			Choose[0] = 1;
		}
		if (MouseX > width / 2 - 150 && MouseX < width / 2 + 180 && MouseY > 500 && MouseY < 550 && isTrigger(MOUSE_LBUTTON)) {
			Sound.clicksound();
			Cur = 2;
			if (Choose[1] == 0)
			Choose[1] = 1;
		}
		if (MouseX < 375 && MouseY > 1030 && isTrigger(MOUSE_LBUTTON)) {
			Sound.clicksound();
			Cur = 3;
			if(Choose[2]==0)
			Choose[2] = 1;
		}
		if (isTrigger(KEY_ENTER)||isTrigger(MOUSE_RBUTTON)) {
			Cur = 0;
		}
		if (Cur != 1) {
			fill(0, 0, 0);
			if (Choose[0] == 1) {
				text("低速移動:長押し", width / 2 - 150, 450);
			}
			if (Choose[0] == 2) {
				text("低速移動:切り替え", width / 2 - 150, 450);
			}
		}
		if (Cur == 1) {
			if (Choose[0] == 1) {
				fill(255, 0, 0);
				text("低速移動:長押し", width / 2 - 150, 450);
			}
			if (Choose[0] == 2) {
				fill(255, 0, 0);
				text("低速移動:切り替え", width / 2 - 150, 450);
			}
			if (Choose[0] == 1 && (isTrigger(KEY_UP) || isTrigger(KEY_DOWN))) {
				Sound.clicksound();
				Player.ControlMode[0] = 2;
				Choose[0] = 2;
			}
			else if (Choose[0] == 2 && (isTrigger(KEY_UP) || isTrigger(KEY_DOWN))) {
				Sound.clicksound();
				Player.ControlMode[0] = 1;
				Choose[0] = 1;
			}
		}
		if (Cur != 2) {
			fill(0, 0, 0);
			if (Choose[1] == 1) {
				text("操作モード:WASD/矢印キー", width / 2 - 150, 550);
			}
			if (Choose[1] == 2) {
				text("操作モード:マウス", width / 2 - 150, 550);
			}
		}
		if (Cur == 2) {
			if (Choose[1] == 1) {
				fill(255, 0, 0);
				text("操作モード:WASD/矢印キー", width / 2 - 150, 550);
			}
			if (Choose[1] == 2) {
				fill(255, 0, 0);
				text("操作モード:マウス", width / 2 - 150, 550);
			}
			if (Choose[1] == 1 && (isTrigger(KEY_UP) || isTrigger(KEY_DOWN))) {
				Sound.clicksound();
				Player.ControlMode[1] = 2;
				Choose[1] = 2;
			}
			else if (Choose[1] == 2 && (isTrigger(KEY_UP) || isTrigger(KEY_DOWN))) {
				Sound.clicksound();
				Player.ControlMode[1] = 1;
				Choose[1] = 1;
			}
		}
		if (Cur != 3) {
			fill(0, 0, 0);
			if (Choose[2] == 1) {
				text("オーディオ:あり", 0, 1080);
			}
			else if (Choose[2] == 2) {
				text("オーディオ:半分", 0, 1080);
			}
			else if (Choose[2] == 3) {
				text("オーディオ:なし", 0, 1080);
			}
		}
		if (Cur == 3) {
			if (Choose[2] == 1) {
				fill(255, 0, 0);
				text("オーディオ:あり", 0, 1080);
			}
			else if (Choose[2] == 2) {
				fill(255, 0, 0);
				text("オーディオ:半分", 0, 1080);
			}
			else if (Choose[2] == 3) {
				fill(255, 0, 0);
				text("オーディオ:なし", 0, 1080);
			}
			if (Choose[2] == 1 && (isTrigger(KEY_UP) || isTrigger(KEY_DOWN))) {
				Sound.clicksound();
				Sound.halfsound();
				Choose[2] = 2;
			}
			else if (Choose[2] == 2 && (isTrigger(KEY_UP) || isTrigger(KEY_DOWN))) {
				Sound.clicksound();
				Sound.mutesound();
				Choose[2] = 3;
			}
			else if (Choose[2] == 3 && (isTrigger(KEY_UP) || isTrigger(KEY_DOWN))) {
				Sound.clicksound();
				Sound.setsound();
				Choose[2] = 1;
			}
		}
		text((let)"" + Player.ControlMode[0], 0, 100);
		text((let)"" + Cur, 0, 150);
		if (isTrigger(KEY_B)) {
			State = TITLE;
		}
	}
	//メイン
	void GAME::Play() {
		clear(20, 255, 255);
		hideCursor();
		fill(255, 255, 255);
		HighScore = Save.loadscore();
		//更新と表示
		Background.draw();
		Player.update();
		Player.draw();
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
							Score += 1000;
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
					Sound.gameoversound();
					Save.savescore(Score);
					State = GAMEOVER;
				}
			}
		}
		for (int i = 0; i < BULLET_ENUM;i++) {
			if (Ebullet[i].Alive) {
				if (Ebullet[i].hit(Player)) {
					Save.savescore(Score);
					Sound.gameoversound();
					State = GAMEOVER;
				}
			}
		}
		
		for (int i = 0; i < ITEM_NUM; i++) {
			if (Item[i].Alive) {
				if (Item[i].hit(Player)) {
					Sound.getitemsound();
					Item[i].Alive = false;
					Player.i++;
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
					Sound.gameoversound();
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
		
		text((let)"Player" + Player.i, 0, 1055);
		text((let)"Player" + Player.i, 0, 1055);
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
			Score += 100000000;
			Save.savescore(Score);
			State = CLEAR;
		}
		if (isTrigger(KEY_T)) {
			Save.savescore(Score);
			State = TITLE;
			Sound.playstopsound();
		}
		Background.secdraw();
		fill(255, 255, 255);
		text((let)"Score " + Score, 0, 50);
		text((let)"HighScore " + HighScore, 0, 100);
		text((let)"Delay " + ShotDelay, 0, 150);
		text("Normal ", 0, 200);
		text((let)"Wave" + Wave, 0, 250);
		text((let)"Limit" + Boss.LimitTime, 0, 300);
		text((let)"" + Player.ControlMode[0], 0, 350);
	}

	void GAME::Hardmode() {
		clear(20, 255, 255);
		hideCursor();
		fill(255, 255, 255);
		HighScore = Save.loadscore();
		//更新と表示
		Background.draw();
		Player.hardupdate();
		Player.draw();
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
						Enemy[e].Delay = rand() % 20 + 20;
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
						Score += 1800;
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
					Sound.playstopsound();
					Save.savescore(Score);
					Sound.gameoversound();
					State = HARDOVER;
				}
			}
		}
		for (int i = 0; i < BULLET_ENUM; i++) {
			if (Ebullet[i].Alive) {
				if (Ebullet[i].hit(Player)) {
					Sound.playstopsound();
					Save.savescore(Score);
					Sound.gameoversound();
					State = HARDOVER;
				}
			}
		}

		for (int i = 0; i < ITEM_NUM; i++) {
			if (Item[i].Alive) {
				if (Item[i].hit(Player)) {
					Sound.getitemsound();
					Item[i].Alive = false;
					Player.i++;
					if (Player.Shotlevel < 4) {
						Player.Shotlevel++;
					}
					else if (Player.Shotlevel >= 4 && ShotDelay > 1) {
						Delay -= 3.0f;
					}
				}
			}
		}
		for (int i = 0; i < BULLET_BNUM; i++) {
			if (Bbullet[i].Alive) {
				if (Bbullet[i].hit(Player)) {
					Save.savescore(Score);
					Sound.playstopsound();
					Sound.gameoversound();
					State = HARDOVER;
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
						Enemy[i].Delay -= 3;
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
			Score += 10000000;
			Save.savescore(Score);
			State = CLEAR;
		}
		if (isTrigger(KEY_T)) {
			Save.savescore(Score);
			Sound.playstopsound();
			State = TITLE;
		}
		Background.secdraw();
		fill(255, 255, 255);
		text((let)"Score " + Score, 0, 50);
		text((let)"HighScore " + HighScore, 0, 100);
		text((let)"Delay " + ShotDelay, 0, 150);
		text("Hard ", 0, 200);
		text((let)"Wave" + Wave, 0, 250);
		text((let)"Limit" + Boss.LimitTime, 0, 300);
		text((let)"" + Player.ControlMode[0], 0, 350);
	}

	void GAME::GameOver() {
		clear(0,0,0);
		HighScore = Save.loadscore();
		Background.gameoverdraw();
		Sound.playstopsound();
		fill(128, 128, 128);
		text((let)"Score " + Score, 0, 100);
		text((let)"HighScore " + HighScore, 0, 150);
		text("GameOver", 0, 50); textSize(50);
		text((let)"BossHp " + Boss.Hp, 0, 200);
		text((let)"Limit" + Boss.LimitTime, 0, 300);

		Player.draw();

		for (int i = 0; i < ITEM_NUM; i++) {
			if (Item[i].Alive) {
				Item[i].draw();
			}
		}
		for (int i = 0; i < BULLET_NUM; i++) {
			if (Bullet[i].Alive) {
				Bullet[i].draw();
			}
		}
		for (int i = 0; i < BULLET_ENUM; i++) {
			if (Ebullet[i].Alive) {
				Ebullet[i].draw();
			}
		}
		for (int i = 0; i < ENEMY_NUM; i++) {
			if (Enemy[i].Alive)
				Enemy[i].draw();
		}
		for (int i = 0; i < BULLET_BNUM; i++) {
			if (Bbullet[i].Alive) {
				Bbullet[i].draw();
			}
		}
		if (Wave == 0) {
			Boss.draw();
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
			ClientToScreen(HWnd, &mouse);
			SetCursorPos(1280, 880);
			Background.Take = 0;
			State = PLAY;
			Sound.playsound();
		}
		if (isTrigger(KEY_T)) {
			State = TITLE;
		}
		
	}

	void GAME::HardOver() {
		clear(0, 0, 0);
		HighScore = Save.loadscore();
		Background.gameoverdraw();
		fill(128, 128, 128);
		text((let)"Score " + Score, 0, 100);
		text((let)"HighScore " + HighScore, 0, 150);
		text("GameOver", 0, 50); textSize(50);
		text((let)"BossHp " + Boss.Hp, 0, 200);
		text((let)"Limit" + Boss.LimitTime, 0, 300);
		Player.draw();
		for (int i = 0; i < ITEM_NUM; i++) {
			if (Item[i].Alive) {
				Item[i].draw();
			}
		}
		for (int i = 0; i < BULLET_NUM; i++) {
			if (Bullet[i].Alive) {
				Bullet[i].draw();
			}
		}
		for (int i = 0; i < BULLET_ENUM; i++) {
			if (Ebullet[i].Alive) {
				Ebullet[i].draw();
			}
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
			ClientToScreen(HWnd, &mouse);
			SetCursorPos(1280, 880);
			Background.Take = 0;
			State = HARD;
			Sound.playsound();
		}
		if (isTrigger(KEY_T)) {
			State = TITLE;
		}

	}

	void GAME::GameClear(){
		clear(128, 228, 228);
		HighScore = Save.loadscore();
		Background.cleardraw();
		Sound.playstopsound();
		rectMode(CENTER);
		fill(100,228,255);
		strokeWeight(10);
		text((let)"Score " + Score, 0, 50);
		text((let)"HighScore " + HighScore, 0, 100);
		text((let)"Limit" + Boss.LimitTime, 0, 150);

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
			else if (State == HARD) {
				Hardmode();
			}
			else if (State == OPTION) {
				Option();
			}
			else if (State == GAMEOVER) {
				GameOver();
			}
			else if (State == CLEAR) {
				GameClear();
			}
			else if (State == HARDOVER) {
				HardOver();
			}
	}
};