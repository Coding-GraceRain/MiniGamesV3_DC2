#include "../../libOne/inc/libOne.h"
#include "ebullet.h"

namespace GAME04 {

	void ENEMYBULLET::draw() {
		if (hp > 0) {
			// ここで弾を描画する
			//fill(255, 255, 0);
			circle(px, py, pr);
		}





	}
	void ENEMYBULLET::move() {
		if (hp > 0) {
			px += vx;
			py += vy;

			// 左右の壁で反射
			if (px < pr / 2 || px > 1920 - pr / 2) {
				vx = -vx;
				px = (px < pr / 2) ? pr / 2 : (1920 - pr / 2);
			}

			// 画面外に出たら非アクティブ
			if (py > 1080 || py < -h) {
				hp = 0;
			}
		}
	}

		
	
	
	void ENEMYBULLET::shoot(float ex, float ey, float vx_, float vy_) {
		if (hp == 0) {
			hp = 1;
			px = ex;
			py = ey;
			vx = vx_;
			vy = vy_;
		}
	}
}