#include "../../libOne/inc/libOne.h"
#include"PLAYER.h"

void PLAYER::init() {
	x = 200;
	y = 860;
	vy = 0;
	jumpCount = 0;
	animeTimer = 0;
	anime = 0;
	isJump = false;
}
void PLAYER::update(int seJump) {
	animeTimer++;
	if (animeTimer % 8 == 0) {  //速さ調整
		anime++;
		if (anime >= 3) {
			anime = 0;
		}
	}

	if (isTrigger(KEY_SPACE) && jumpCount < 2) {
		vy = -14;  //jump hight
		jumpCount++;
		isJump = true;
		playSound(seJump);
	}

	if (isPress(KEY_SPACE)) {
		vy -= 0.3f;
	}
	vy += 0.7f;
	y += vy;
	if (isPress(KEY_S)) {
		vy += 1.5f;
	}
	if (y > 860) {
		y = 860;
		vy = 0;
		jumpCount = 0;
		isJump = false;
	}

}
void PLAYER::draw(int imgSoldier[3]) {
	image(imgSoldier[anime], x - 10, y, 4, 4);
	rect(x + 30, y + 20, 40, 90);
}