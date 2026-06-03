#include "BBULLET.h"
#include "../../libOne/inc/graphic.h"
#include "../../libOne/inc/mathUtil.h"
#include <cmath>
namespace GAME02 {
	void BBULLET::create() {
		Img = loadImage("../main\\assets\\game02\\bossdanmaku.png");

	}
	void BBULLET::init() {
		Alive = false;
	}
	void BBULLET::set(float x, float y,float vx,float vy) {

		Bx = x; 
		By = y;
		Vx = vx;
		Vy = vy;
		Alive = true;

	}
	void BBULLET::update() {
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
		if (Bx > 1240) {
			Alive = false;
		}
		if (Bx < 640) {
			Alive = false;
		}
	}
	void BBULLET::draw() {
		if (Alive) {
			image(Img, Bx, By, -10);
		}
		

	}
	float BBULLET::left() { return Bx - 8; }
	float BBULLET::right() { return Bx + 8; }
	float BBULLET::top() { return By - 8; }
	float BBULLET::bottom() { return By + 8; }

	bool BBULLET::hit(PLAYER& player) {
		if (left() > player.right() ||
			right() < player.left() ||
			top() > player.bottom() ||
			bottom() < player.top()) {
			return false;
		}
		return true;
	}



}