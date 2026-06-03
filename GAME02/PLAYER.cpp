#include"../../libOne/inc/graphic.h"
#include "../../libOne/inc/input.h"
#include"ENEMY.h"
#include "PLAYER.h"

namespace GAME02 {
	void PLAYER::create() {
		Img = loadImage("../main\\assets\\game02\\reimu.png");
	}
	void PLAYER::init() {
		Px = width / 2 ;
		Py = height -220;
		Bom = 1;
		Shotlevel = 4;
	}

	void PLAYER::update() {
		Vx = 4.0f;
		Vy = 4.0f;
		if (isPress(KEY_SHIFT)) {
			Vx = 1.5f;
			Vy = 1.5f;
		}
		if (isPress(KEY_A)) {
			Px -= Vx;
		}
		if (isPress(KEY_D)) {
			Px += Vx;
		}
		if (isPress(KEY_W)) {
			Py -= Vy;
		}
		if (isPress(KEY_S)) {
			Py += Vy;
		}
		if (Px < 642) {
			Px = 643;
		}
		if (Px > 1278){
			Px = 1277;
		}
		if (Py < 0) {
			Py = 1;
		}
		if (Py > 1080) {
			Py = 1079;
		}

	}
	void PLAYER::sibariupdate() {
		Vx = 5.0f;
		Vy = 5.0f;
		if (isPress(KEY_SHIFT)) {
			Vx = 2.5f;
			Vy = 2.5f;
		}
		if (isPress(KEY_A)) {
			Px -= Vx;
		}
		if (isPress(KEY_D)) {
			Px += Vx;
		}
		if (isPress(KEY_W)) {
			Py -= Vy;
		}
		if (isPress(KEY_S)) {
			Py += Vy;
		}
		if (Px < 642) {
			Px = 643;
		}
		if (Px > 1278) {
			Px = 1277;
		}
		if (Py < 0) {
			Py = 1;
		}
		if (Py > 1080) {
			Py = 1079;
		}

	}
	void PLAYER::draw() {
		rectMode(CENTER);
		image(Img, Px, Py);
	}
	float PLAYER::left() { return Px-1; }
	float PLAYER::right() { return Px + 1; }
	float PLAYER::top() { return Py-1; }
	float PLAYER::bottom() { return Py + 1; }
	bool PLAYER::hit(ENEMY& enemy) {
		if (left() > enemy.right() ||
			right() < enemy.left() ||
			top() > enemy.bottom() ||
			bottom() < enemy.top()) {
			return false;
		}
		return true;
	}
}