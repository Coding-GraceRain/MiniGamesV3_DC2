#include "../../libOne/inc/libOne.h"

#include "GAME04.h"
#include "player.h"

namespace GAME04 {
	
	void PLAYER::move() {
		//posx = posx + 5.0f;
		
		if (isPress(KEY_A)) { px += -vx; }
		if (isPress(KEY_D)) { px += vx; }
		if (isPress(KEY_S)) { py += vx; }
		if (isPress(KEY_W)) { py += -vx; }
		if (py < 1080 / 2) {
			if (isPress(KEY_W)) { py += vx; }

		}
		

		
		if (py < 0) py = 0;
		if (py > 1080) py = 1080;
		if (px < 0) px = 0;
		if (px > 1920) px = 1920;

		
	}

	void PLAYER::draw() {

		rectMode(CENTER);
		//fill(255, 255, 0);
		circle(px, py, pr);
	}


	

	void PLAYER::ku() {

	
	}
}