#include "MULTI.h"
#include "SAIKORO.h"
#include "../../libOne/inc/libOne.h"

void MULTI1::set(int x, int y,int n) {

	//srand(time(0));
	if (isTrigger(KEY_I) && cnt[0] < num[0] && cnt[1] < num[1] && Flag[0] == 0 && Flag[1] == 1) {
		A = random() % 6 + 1;
		B = random() % 6 + 1;
		C = random() % 6 + 1;
		cnt[0]++;

		i = 1;
	}

	rectMode(CORNER);
	fill(0);
	rect(1520, 0, 400, 200);

	rect(1420, 0, 100, 100);
	textSize(80);
	if (n == 1) {
		fill(255, 0, 0);
		text("e", 1430, 90);
	}
	else {
		fill(255);
		text("Žq", 1430, 90);
	}

	fill(255);
	stroke(255);
	strokeWeight(3);
	line(1920 - 400, 50, 1920, 50);
	line(1920 - 400, 100, 1920, 100);
	line(1920 - 400, 150, 1920, 150);
	line(1920 - 125, 50, 1920 - 125, 200);

	textSize(50);
	text("PLAYER2", 1920 - 290, 50);//60?
	text("ŽèŽ‚¿‹à", 1920 - 390, 100);
	text("Š|‚¯‹à", 1920 - 390, 150);
	text("U‚ê‚é‰ñ”", 1920 - 390, 200);
	text(Coin, 1920 - 120, 100);
	text(Coinkake, 1920 - 120, 150);
	text(num[0] - cnt[0], 1920 - 120, 200);


	rectMode(CENTER);
	image(Img[A], x, y);
	image(Img[B], x + 200, y);
	image(Img[C], x + 400, y);


	if (i > 0 && i < 11)i++;
	if (i > 1 && i < 10)kari(x, y);

}

void MULTI2::set(int x, int y,int n) {

	if (isTrigger(KEY_O) && cnt[0] < num[0] && cnt[1] < num[1] && Flag[0] == 0 && Flag[1] == 1) {
		A = random() % 6 + 1;
		B = random() % 6 + 1;
		C = random() % 6 + 1;
		cnt[0]++;

		i = 1;
	}

	rectMode(CORNER);
	fill(0);
	rect(0, 880, 400, 200);

	rect(400, 980, 100, 100);
	textSize(80);
	if (n == 2) {
		fill(255, 0, 0);
		text("e", 410, 1070);
	}
	else {
		fill(255);
		text("Žq", 410, 1070);
	}

	fill(255);
	stroke(255);
	strokeWeight(3);
	line(0, 1080 - 50, 400, 1080 - 50);
	line(0, 1080 - 100, 400, 1080 - 100);
	line(0, 1080 - 150, 400, 1080 - 150);
	line(275, 1080, 275, 1080 - 150);

	textSize(50);
	text("PLAYER3", 110, 1080 - 150);//60?
	text("ŽèŽ‚¿‹à", 10, 1080 - 100);
	text("Š|‚¯‹à", 10, 1080 - 50);
	text("U‚ê‚é‰ñ”", 10, 1080);
	text(Coin, 280, 1080 - 100);
	text(Coinkake, 280, 1080 - 50);
	text(num[0] - cnt[0], 280, 1080);


	rectMode(CENTER);
	image(Img[A], x, y);
	image(Img[B], x + 200, y);
	image(Img[C], x + 400, y);


	if (i > 0 && i < 11)i++;
	if (i > 1 && i < 10)kari(x, y);
}

void MULTI3::set(int x, int y,int n) {
	if (isTrigger(KEY_P) && cnt[0] < num[0] && cnt[1] < num[1] && Flag[0] == 0 && Flag[1] == 1) {
		A = random() % 6 + 1;
		B = random() % 6 + 1;
		C = random() % 6 + 1;
		cnt[0]++;

		i = 1;
	}

	rectMode(CORNER);
	fill(0);
	rect(1520, 880, 400, 200);

	rect(1420, 980, 100, 100);
	textSize(80);
	if (n == 3) {
		fill(255, 0, 0);
		text("e", 1430, 1070);
	}
	else {
		fill(255);
		text("Žq", 1430, 1070);
	}

	fill(255);
	stroke(255);
	strokeWeight(3);
	line(1920 - 400, 1080 - 50, 1920, 1080 - 50);
	line(1920 - 400, 1080 - 100, 1920, 1080 - 100);
	line(1920 - 400, 1080 - 150, 1920, 1080 - 150);
	line(1920 - 125, 1080, 1920 - 125, 1080 - 150);

	textSize(50);
	text("PLAYER4", 1920 - 290, 1080 - 150);//60?
	text("ŽèŽ‚¿‹à", 1920 - 390, 1080 - 100);
	text("Š|‚¯‹à", 1920 - 390, 1080 - 50);
	text("U‚ê‚é‰ñ”", 1920 - 390, 1080);
	text(Coin, 1920 - 120, 1080 - 100);
	text(Coinkake, 1920 - 120, 1080 - 50);
	text(num[0] - cnt[0], 1920 - 120, 1080);


	rectMode(CENTER);
	image(Img[A], x, y);
	image(Img[B], x + 200, y);
	image(Img[C], x + 400, y);


	if (i > 0 && i < 11)i++;
	if (i > 1 && i < 10)kari(x, y);
}