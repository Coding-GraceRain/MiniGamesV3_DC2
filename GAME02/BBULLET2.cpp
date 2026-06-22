#include "BBULLET2.h"
#include "../../libOne/inc/graphic.h"
#include "../../libOne/inc/mathUtil.h"
#include <cmath>
namespace GAME02 {
	void BBULLET2::create() {
		Img = loadImage("../main\\assets\\game02\\danmaku.png");

	}
	void BBULLET2::init() {
		Alive = false;
	}
	void BBULLET2::set(float x, float y, float vx, float vy) {

		Bx = x;
		By = y;
		Vx = vx;
		Vy = vy;
		Alive = true;

	}

	void BBULLET2::update() {
		if (!Alive) {
			return;
		}
		Bx += Vx;
		By += Vy;
		if (By > 1080) {
			Alive = false;
		}
		if (By < 0) {
			Alive = false;
		}
		if (Bx > 1920) {
			Alive = false;
		}
		if (Bx < 640 + 24) {
			Alive = false;
		}
	}
	void BBULLET2::draw() {
		if (Alive) {
			image(Img, Bx, By, -10);
		}
	}

	float BBULLET2::left() { return Bx - 25; }
	float BBULLET2::right() { return Bx + 25; }
	float BBULLET2::top() { return By - 25; }
	float BBULLET2::bottom() { return By + 25; }

	bool BBULLET2::hit(PLAYER& player) {
		if (left() < player.right() &&
			right() > player.left() &&
			top() < player.bottom() &&
			bottom() > player.top()) {
			return true;
		}
		return false;
	}


}
