#include "PLAYER.h"
#include "../../libOne/inc/graphic.h"
#include "../../libOne/inc/input.h"
namespace GAME06 
{
	PLAYER::PLAYER() {
		Px = width / 2;
		Py = height - 120;
		W = 80;
		H = 160;
		Vx = 6;
		OfsY = -80;
		Hp = 100;
	}

	PLAYER::~PLAYER() {

	}

	void PLAYER::init() {
		Px = width / 2;
		Py = height - 120;
		W = 80;
		H = 160;
		Vx = 6;
		OfsY = -80;
		Hp = 100;
	}

	void PLAYER::update() {
		if (isPress(KEY_A))Px += -Vx;
		if (isPress(KEY_D))Px += Vx;
	}

	void PLAYER::draw() {
		textSize(50);
		fill(0, 240, 0);
		text((let)"HPÅF" + Hp, Px - W / 2, Py + H / 2);
		rectMode(CENTER);
		strokeWeight(1);
		fill(0, 210, 0);
		rect(Px, Py, W, H);
	}

	void PLAYER::proc() {
		update();
		draw();
	}
}