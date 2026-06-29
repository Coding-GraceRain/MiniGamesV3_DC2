/*
#include "SORO.h"
#include "SAIKORO.h"
#include "../../libOne/inc/libOne.h"

void SORO::set(int x, int y,int f) {

	//抽選
	if (f == 1 && cnt[0] < 1 && cnt[1] < num[1] && Flag == 0) {
		A = random() % 6 + 1;
		B = random() % 6 + 1;
		C = random() % 6 + 1;
		i = 1;
		cnt[0]++;
	}
	else if (f == 1 && cnt[0] < num[0] && cnt[1] < num[1] && Flag == 0 && i == 11) {
		A = random() % 6 + 1;
		B = random() % 6 + 1;
		C = random() % 6 + 1;
		i = 1;
		cnt[0]++;
	}
	
	rectMode(CORNER);
	fill(0);
	rect(1520, 0, 400, 200);

	fill(255);

	stroke(255);
	strokeWeight(3);
	line(1920 - 400, 50, 1920, 50);
	line(1920 - 400, 100, 1920, 100);
	line(1920 - 400, 150, 1920, 150);
	line(1920 - 125, 50, 1920 - 125, 200);

	text("BOT", 1920 - 290, 50);//60?
	text("手持ち金", 1920 - 390, 100);
	text("掛け金", 1920 - 390, 150);
	text("振れる回数", 1920 - 390, 200);
	text(Coin, 1920 - 120, 100);
	text(Coinkake, 1920 - 120, 150);
	text(num[0] - cnt[0], 1920 - 120, 200);

	//さいころ表示
	rectMode(CENTER);
	image(Img[A], x, y);
	image(Img[B], x + 200, y); 
	image(Img[C], x + 400, y);

	//シャッフル演出
	if (i > 0 && i < 11)i++;
	if (i > 1 && i < 10) kari(1200, 300);


}
*/