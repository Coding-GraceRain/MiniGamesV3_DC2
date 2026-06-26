#include "../../libOne/inc/libOne.h"
#include "ENEMY.h"


void ENEMY::init(){}
void ENEMY::update(float speed){}
void ENEMY::draw(){}

void OBAKE::init() {
	x = 1900 + rand() % 300  ;
	y = rand() % 50 + 860;
	anime = 0;
	animeTimer = 0;
	hp = 5;
	w = 50;
	h = 50;
}
void KOUMORI::init() {
	x = 1900 + rand() % 800;
	y = rand() % 300 + 450;
	anime = 0;
	animeTimer = 0;
	hp = 2;
	w = 20;
	h = 20;
}

void OBAKE::update(float speed) {
	x -= speed;
	if (x < -50) {
		x = 1920 + rand() % 500;
	}
	animeTimer++;
	if (animeTimer % 8 == 0) {  //速さ調整
		anime++;
		if (anime >= 3) {
			anime = 0;
		}
	}
}
void KOUMORI::update(float speed) {
	x -= speed;
	if (x < -50) {
		x = 1920 + rand() % 500;
	}
	animeTimer++;
	if (animeTimer % 8 == 0) {  //速さ調整
		anime++;
		if (anime >= 3) {
			anime = 0;
		}
	}
}

void OBAKE::draw() {
	image(img[anime], x - 30, y - 30, 4, 4);
	rect(x, y, w, h);
}
void KOUMORI::draw() {
	image(img[anime], x-70 , y-60 , 5, 5);
	rect(x , y , w, h);
}

void OBAKE::damage() {
	hp--;
	if (hp <= 0) {
		init();
	}
}
void KOUMORI::damage() {
	hp--;
	if (hp <= 0) {
		init();
	}
}

