#include "../../libOne/inc/libOne.h"
#include "bullet.h"
#include "player.h"

namespace GAME04 {
	
		void BULLET::move() {
			if (hp > 0) {
				py += vy;
				if (py < -h) {
					hp = 0;
				}
			}

			
		}
		void BULLET::draw() {
			rectMode(CENTER);
			if (hp > 0) {
				circle(px, py, pr);
			}
		}
	
		void BULLET::shoot(float x, float y) {
			if (hp == 0) {
				hp = 1;
				px = x;
				py = y;
			}
		}

}