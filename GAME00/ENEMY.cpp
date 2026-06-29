#include "../../libOne/inc/graphic.h"
#include "../../libOne/inc/window.h"
#include "ENEMY.h"
namespace GAME00
{
	void ENEMY::create() {
		Img = loadImage("../main/assets/game00/tori.png");
		ImgRight = loadImage("../main/assets/game00/tori2.png");

		for (int i = 0; i < Bullet_Max; i++) {
			Bullet[i].create();
		}
	}
	void ENEMY::init(float x, float y) {
		Px = x;
		Py = y;
		Vx = 300.0f;
		Vy = 5.0f;
		isRight = true;
		ShotTimer = 0.0f;
	}
	void ENEMY::update() {
		Px += Vx * delta;
		if (right() >= width) {
			Px = width - 120;
			Vx *= -1;
			isRight = false;
		}
		if (left() <= 0) {
			Px = 0;
			Vx *= -1;
			isRight = true;
		}
		ShotTimer += delta;

		if (ShotTimer >= 3.0f) {

			for (int i = 0; i < Bullet_Max; i++) {

				if (!Bullet[i].isActive()) {

					Bullet[i].init(Px + 60, Py + 80, 0.0f, 500.0f);

					break;
				}
			}

			ShotTimer = 0.0f;
		}
		for (int i = 0; i < Bullet_Max; i++) {
			Bullet[i].update();
		}
	}
	void ENEMY::moveY(float dy) {
		Py += dy;
	}
	void ENEMY::moveBulletY(float dy) {
		for (int i = 0; i < Bullet_Max; i++) {
			Bullet[i].moveY(dy);
		}
	}
	void ENEMY::draw() {
		if (isRight) {
			image(Img, Px, Py);
		}
		else {
			image(ImgRight, Px, Py);
		}
		for (int i = 0; i < Bullet_Max; i++) {
			Bullet[i].draw();
		}

	}

	float ENEMY::left() { return Px + 65; }
	float ENEMY::right() { return Px + 120; }
	float ENEMY::top() { return Py; }
	float ENEMY::bottom() { return Py + 180; }

	BULLET& ENEMY::getbullet(int i) {
		return Bullet[i];
	}
}