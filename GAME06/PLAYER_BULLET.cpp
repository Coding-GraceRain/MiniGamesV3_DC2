#include "PLAYER_BULLET.h"
#include "../../libOne/inc/graphic.h"
#include "../../libOne/inc/input.h"
#include "GAME06.h"
#include "PLAYER.h"
namespace GAME06 
{
	PLAYER_BULLET::PLAYER_BULLET(){
		Px = width / 2;
		Py = height - 120;
		W = 15;
		H = 30;
		Vy = -10;
	}

	PLAYER_BULLET::~PLAYER_BULLET() {

	}

	void PLAYER_BULLET::init() {
		Px = width / 2;
		Py = height - 120;
		W = 15;
		H = 30;
		Vy = -10;
	}

	void PLAYER_BULLET::shot() {
		if (Flag) {
			Py += Vy;
			if (Py < -H) {
				Flag = false;
			}
		}
	}

	void PLAYER_BULLET::draw() {
		if (Flag) {
			rectMode(CENTER);
			strokeWeight(1);
			fill(30, 240, 10);
			rect(Px, Py, W, H);
		}
	}
}