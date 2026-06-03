#include "EBULLET.h"
#include <cmath>
#include "../../libOne/inc/mathUtil.h"
#include "../../libOne/inc/graphic.h"
namespace GAME02 {
	void EBULLET::create() {
		Img = loadImage("../main\\assets\\game02\\bluebullet.png");

	}
	void EBULLET::init() {
		//angleMode(DEGREES);
		//deg = 0;
		Alive = false;
	}
	void EBULLET::shoot(int x, int y) {
		Bx = x;// + sin(deg);
		By = y;// sin(deg);
		Vy = 1.3f;// cos(deg);
		Alive = true;

	}
	void EBULLET::update() {
		if (!Alive) {
			return;
		}

		By += Vy;
		//deg += 0.1f;
		if (By > 1080) {
			Alive = false;
		}
		if (By < 0) {
			Alive = false;
		}
		if (Bx > 1240) {
			Alive = false;
		}
		if (Bx < 640) {
			Alive = false;
		}
	}
	void EBULLET::draw() {
		if (Alive) {
			image(Img, Bx, By,-90);
		}

	}
	float EBULLET::left() { return Bx - 8; }
	float EBULLET::right() { return Bx + 8; }
	float EBULLET::top() { return By - 8; }
	float EBULLET::bottom() { return By + 8; }

	bool EBULLET::hit(PLAYER& player) {
		if (left() > player.right() ||
			right() < player.left() ||
			top() > player.bottom() ||
			bottom() < player.top()) {
			return false;
		}
		return true;
	}



}
