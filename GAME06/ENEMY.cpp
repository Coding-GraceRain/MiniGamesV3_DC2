#include "ENEMY.h"
#include "../../libOne/inc/graphic.h"
#include "../../libOne/inc/mathUtil.h"
namespace GAME06
{
	ENEMY::ENEMY() {
		Px = width / 2;
		Py = 150;
		W = 150;
		H = 150;
		OfsY = 75;
		Angle = 0;
		AngleSpeed = 1.0f;
		Hp = 100;
	}

	ENEMY::~ENEMY() {

	}

	void ENEMY::init() {
		Px = width / 2;
		Py = 150;
		W = 150;
		H = 150;
		OfsY = 75;
		Angle = 0;
		AngleSpeed = 1.0f;
		Hp = 100;
	}

	void ENEMY::update() {
		angleMode(DEGREES);
		Angle += AngleSpeed;
		Px = Sin(Angle) * 800 + width / 2;
	}

	void ENEMY::draw() {
		textSize(50);
		fill(255, 0, 0);
		text((let)"HPÅF" + Hp, Px - W / 2, Py + H );
		rectMode(CENTER);
		strokeWeight(1);
		fill(200, 0, 200);
		rect(Px, Py, W, H);
	}
}