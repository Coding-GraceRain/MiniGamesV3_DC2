#include "ENEMY_BULLET.h"
#include "../../libOne/inc/graphic.h"
#include "GAME06.h"
#include "ENEMY.h"
#include "PLAYER.h"
namespace GAME06 
{
	ENEMY_BULLET::ENEMY_BULLET(){
		Px = width / 2;
		Py = 150;
		W = 50;
		H = 50;
		Vy = 10;
	}

	ENEMY_BULLET::~ENEMY_BULLET() {

	}

	void ENEMY_BULLET::init() {
		Px = width / 2;
		Py = 150;
		W = 50;
		H = 50;
		Vy = 10;
	}

	void ENEMY_BULLET::shot() {
		if (Flag) {
			Px += Vx;
			Py += Vy;
			if (Py > height + H / 2) {
				Flag = false;
			}
		}
	}

	void ENEMY_BULLET::draw() {
		if (Flag) {
			rectMode(CENTER);
			strokeWeight(1);
			fill(220, 0, 180);
			rect(Px, Py, W, H);
		}
	}
}