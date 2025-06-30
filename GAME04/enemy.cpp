#include "../../libOne/inc/libOne.h"

#include "enemy.h"

namespace GAME04{

    void ENEMY::draw() {
		rectMode(CENTER);
		circle(px, py, pr);
    }
	
    void  ENEMY::move() {
		px += vx;
		if (px > 1920 || px < 0) {
			vx *= -1;
		}
	}

	void  ENEMY::mik() {
		
	}

	void  ENEMY::fn() {
		//ing = loadImage("../MAIN/assets/game04/スクリーンショット 2025-04-11 125309.png");
    }
}
