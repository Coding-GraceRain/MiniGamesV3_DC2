#include "../../libOne/inc/libOne.h"
#include "../MAIN/MAIN.h"
#include "GAME04.h"
#include "PLAYER.h"
#include"ENEMY.h"


namespace GAME04
{
	static bool hit(float x1, float y1, float w1, float h1,
		float x2, float y2, float w2, float h2)
	{
		return (x1 < x2 + w2 &&
			x1 + w1 > x2 &&
			y1 < y2 + h2 &&
			y1 + h1 > y2);
	}
	int GAME::create()
	{
		imgHaikei= loadImage("../main/assets/game04/haikei4.png");
		imgSoldier[0] = loadImage("../main/assets/game04/pipo-charachip_soldier001.png");
		imgSoldier[1] = loadImage("../main/assets/game04/pipo-charachip_soldier002.png");
		imgSoldier[2] = loadImage("../main/assets/game04/pipo-charachip_soldier003.png");
		imgKoumori[0] = loadImage("../main/assets/game04/koumori1.png");
		imgKoumori[1] = loadImage("../main/assets/game04/koumori2.png");
		imgKoumori[2] = loadImage("../main/assets/game04/koumori3.png");
		imgObake[0] = loadImage("../main/assets/game04/obake01.png");
		imgObake[1] = loadImage("../main/assets/game04/obake02.png");
		imgObake[2] = loadImage("../main/assets/game04/obake03.png");
		imgClearEffect[0] = loadImage("../main/assets/game04/congratulations-01.png");
		imgClearEffect[1] = loadImage("../main/assets/game04/congratulations-02.png");
		imgClearEffect[2] = loadImage("../main/assets/game04/congratulations-03.png");
		imgClearEffect[3] = loadImage("../main/assets/game04/congratulations-04.png");
		imgClearEffect[4] = loadImage("../main/assets/game04/congratulations-05.png");
		imgClearEffect[5] = loadImage("../main/assets/game04/congratulations-06.png");
		imgClearEffect[6] = loadImage("../main/assets/game04/congratulations-07.png");
		imgClearEffect[7] = loadImage("../main/assets/game04/congratulations-08.png");
		imgClearEffect[8] = loadImage("../main/assets/game04/congratulations-09.png");
		imgClearEffect[9] = loadImage("../main/assets/game04/congratulations-10.png");
		imgTitle = loadImage("../main/assets/game04/titleImage.png");
		imgMenu[0] = loadImage("../main/assets/game04/press space_100.png");
		imgMenu[1] = loadImage("../main/assets/game04/controls_100.png");
		imgMenu[2] = loadImage("../main/assets/game04/exit_100.png");
		imgcarsol=loadImage("../main/assets/game04/carsol.png");
		imgcontrolgamen=loadImage("../main/assets/game04/controlgamen1.png");
		imginfo=loadImage("../main/assets/game04/info.png");
		imgcleargamen=loadImage("../main/assets/game04/cleargamen.png");
		imgGoal=loadImage("../main/assets/game04/goal.png");

		seJump=loadSound("../main/assets/game04/1c880042.wav");
		setVolume(seJump, 0.1f);
		state = TITLE;

		return 0;
	}
	void GAME :: init() {
		player.init();

		for (int i = 0; i < 10; i++) {
			bActive[i] = false;
		}
		speed = 8;
		
		haikeix = 0;
		for (int i = 0; i < 5; i++) {
			obake[i].setImage(imgObake);
			obake[i].init();

			obake[i].setx(1200 + i * 350);

			koumori[i].setImage(imgKoumori);
			koumori[i].init();

			koumori[i].setx(1200+i*350);
		}


		for (int i = 0; i < 3; i++) {
			fx[i] = 1800 + i * 300;
			if (rand() % 3 == 0) {
				fy[i] = 600;
			}
			else {
				fy[i] = 700;
			}
		}
		clearinit = false;

		gx = 1920;
		gy = 250;
		ginit = 1000;           //goalの位置
		score = 0;
		distance = ginit;       //goal までの距離表記

	}

	void GAME::destroy()
	{

	}
	void GAME::collision() {
		float px = player.getx() + 20;
		float py = player.gety() + 25;
		float pw = player.getw(); 
		float ph = player.geth(); 
		for (int i = 0; i < 5; i++) {
			float ox = obake[i].getx();
			float oy = obake[i].gety();
			float ow = obake[i].getw();
			float oh = obake[i].geth();
			if (hit(px, py, pw, ph, ox, oy, ow, oh)) {
				state = GAMEOVER;
			}
		}
		for (int i = 0; i < 5; i++) {
			float kx = koumori[i].getx();
			float ky = koumori[i].gety();
			float kw = koumori[i].getw();;
			float kh = koumori[i].geth(); 
			if (hit(px, py, pw, ph, kx, ky, kw, kh)) {
				state = GAMEOVER;
			}
		}
		for (int i = 0; i < 10; i++) {
			if (!bActive[i])continue;
			float bx1 = bx[i];
			float by1 = by[i];
			float bw = 10;
			float bh = 10;
			for (int j = 0; j < 5; j++) {
				float ox = obake[j].getx();
				float oy = obake[j].gety();
				float ow = obake[j].getw(); 
				float oh = obake[j].geth(); 
				if (hit(bx1, by1, bw, bh, ox, oy, ow, oh)) {
					bActive[i] = false;
					obake[j].damage();
					break;
				}
				float kx = koumori[j].getx();
				float ky = koumori[j].gety();
				float kw = koumori[j].getw();
				float kh = koumori[j].geth(); 
				if (hit(bx1, by1, bw, bh, kx, ky, kw, kh)) {
					bActive[i] = false;
					koumori[j].damage();
					break;
				}
			}
		}
	}
	void GAME::proc()
	{

		if (state == TITLE) {
			if (isTrigger(KEY_UP)) {
				select--;
				if (select < 0)select = 2;
			}
			if (isTrigger(KEY_DOWN)) {
				select++;
				if (select > 2)select = 0;
			}
			
			if (isTrigger(KEY_SPACE)) {
				if (select == 0) {
					init();
					state = INFO;
				}
				else if (select == 1) {
					state = CONTROL;
				}
				else if (select == 2) {
					main()->backToMenu();
				}
			}
			clear(0, 0, 64);
			image(imgTitle, 0, 0, 0, 1.2f);
			textSize(50);
			fill(255, 255, 0);
			text("GAME04", 0, 100);
			for (int i = 0; i < 3; i++) {
				float x = width / 2 - 240;
				float y = 650 + i * 120;
				float s = 0.3f;
				image(imgMenu[i], x, y, 0, s);
				if (i == select) {

					image(imgcarsol, x - 160, y - 70, 0, 0.2f);
				}
			}
		}
		else if (state == CONTROL) {
			float x = 700;
			clear(0, 0, 64);
			image(imgcontrolgamen, 0, 0, 0, 1.2f);
			if (isTrigger(KEY_SPACE)) {
				state = TITLE;
			}
		}
		else if (state == INFO) {
			clear(0, 0, 64);
			image(imginfo, 0, 0, 0, 1.2f);
			if (isTrigger(KEY_SPACE)) {
				state = PLAY;
			}
		}
			
		
		else if (state == PLAY) {
			clear(255,255,255);
			player.update(seJump);
			for (int i = 0; i < 5; i++) {
				obake[i].update(speed);
				koumori[i].update(speed);
			}
			collision();
			
			image(imgHaikei, haikeix,0,0,1.2f);
			image(imgHaikei, haikeix + 1920,0, 0,1.2f);
			haikeix -= speed * 0.3f;

			player.draw(imgSoldier);
			for (int i = 0; i < 5; i++) {
				obake[i].draw();
				koumori[i].draw();
			}
			if (haikeix < -1920) {
				haikeix = 0;
			}

			text("ゴールまで", 0, 50);
			score++;
			distance--;
			text(distance, 250, 50);
			
			speed += 0.003f;

			for (int i = 0; i < 3; i++) {
				fx[i] -= speed;
				if (fx[i] < -50) {
					fx[i] = 1920 + rand() % 500;
					if (rand() % 3 == 0) {
						fy[i] = 600;
					}
					else {
						fy[i] = 750;
					}
				}
				rect(fx[i], fy[i], 100,10);
			}

	
			if (isTrigger(KEY_F)) {                      //弾
				for (int i = 0; i < 10; i++) {
					if (!bActive[i]) {
						bx[i] = player.getx() + 50; //pの右
						by[i] = player.gety() + 40; //高さ調整
						bActive[i] = true;
						break;
					}
				}
			}
			for (int i = 0; i < 10; i++) {
				if (bActive[i]) {
					bx[i] += 10;
					if (bx[i] > 1920) {
						bActive[i] = false;
					}
					rect(bx[i], by[i], 10, 10);
				}
			}

			float playerBottom = player.gety() + 110;      //足場
			for (int i = 0; i < 3; i++) {
				if (player.getvy() > 0 &&
					playerBottom > fy[i] &&
					playerBottom<fy[i] + 20 &&
					player.getx() + 70>fx[i] &&
					player.getx() + 30 < fx[i] + 100)
				{
					player.setY(fy[i] - 110);
					player.setVy(0);
					player.resetjump();
				}
			}
			//goal goal goal goal goal
			const int goal = ginit;                        
			if (score > goal) {
				state = CLEAR;

			}
			if (score > goal - 200) {
				gx-=speed;
				image(imgGoal, gx, gy, 0.0f, 0.6f);
			}
		}
		else if (state == CLEAR) {
			clear(0, 0, 0);
			if (!clearinit) {
				drawTime = 0;
				drawTimer = 0;
				drawTime2 = 0;
				efectend = false;
				clearinit = true;
			}
			drawTimer++;
			if (!efectend) {
				if (drawTimer % 5 == 0) {       //速さ調整
					drawTime2++;
				}
				if (drawTime2 >= 9) {
					efectend = true;
				}

				image(imgClearEffect[drawTime2], 320, 60);
			}
			else {
				image(imgcleargamen,0, 0, 0, 1.2f);
				if (isTrigger(KEY_SPACE)) {
					state = TITLE;
					clearinit = false;
				}
			}
			
		}
		else if (state == GAMEOVER) {
			textSize(50);
			fill(255,0,0);
			text("GAME OVER", 100, 200);
			text("SPACEで戻る", 200, 300);
			if (isTrigger(KEY_SPACE)) {
				state = TITLE;
				player.init();
				for (int i = 0; i < 5; i++) {
					obake[i].init();
					koumori[i].init();
				}
				
			}
		}
		if (isTrigger(KEY_ENTER)) {
			main()->backToMenu();
		}
	}
}
