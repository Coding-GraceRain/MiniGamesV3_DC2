#include "ENEMY.h"
#include"GAME02.h"
#include<time.h>
#include "../../libOne/inc/graphic.h"
namespace GAME02 {
	void ENEMY::create() {
		Img = loadImage("../main\\assets\\game02\\ster.png");
		srand((unsigned)time(NULL));
		Buf = 0;
	}
	void ENEMY::init() {
			Px = 664 + rand()% 1227;
			Py = rand() % 400;
			Vx = 2.0f;
			Vy = 0.1f;
			Cum = 1000;
			Hp = 5;
			Delay = 0;
			Alive = true;
	}
	void ENEMY::update() {
		if (Cum <= 0) {
			Rnd = rand() % 2;
			Cum = rand() % 300 + 300;
		}
		if (Rnd == 0) {
			Px += Vx;
			Cum -= 1;
		}
		else if (Rnd == 1) {
			Px -= Vx;
			Cum -= 1;

		}
		else
			Px += Vx;

		if (Px< width / 3+24 || Px>width-24) { Vx *= -1; }
	
		if (Py < 24) {
			init();
		}
	
	}
	void ENEMY::draw() {
		rectMode(CENTER);
		image(Img, Px, Py);
	}

	bool ENEMY::drop() {
		return rand() % 100 < 15;
	}
	bool ENEMY::harddrop() {
		return rand() % 100 < 5;
	}
	float ENEMY::left() { return Px-24.0f; }
	float ENEMY::right() { return Px + 24.0f; }
	float ENEMY::top() { return Py-24.0f; }
	float ENEMY::bottom() { return Py + 24.0f; }
	bool ENEMY::hit(ENEMY& enemy) {
		if (left() > enemy.right() ||
			right() < enemy.left() ||
			top() > enemy.bottom() ||
			bottom() < enemy.top()) {
			return false;
		}
		return true;
	}
}