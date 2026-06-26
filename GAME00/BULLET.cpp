#include"../../libOne/inc/graphic.h"
#include"../../libOne/inc/window.h"
#include<math.h>
#include "BULLET.h"
namespace GAME00
{
	void BULLET::create() {
		Img = loadImage("../main/assets/game00/bullet.png");
		Active = false;
	}

	void BULLET::init(float x, float y, float vx, float vy) {
		Px = x;
		Py = y;
		Vx = vx;
		Vy = vy;

		BaseX = x;
		Timer = 0.0f;
		Active = true;
	}

	void BULLET::update() {
		if (!Active)
			return;

		Timer += delta;

		Px = BaseX + sin(Timer * 4.0f) * 80.0f;
		Py += Vy * delta;

		if (Py > height + 100) {
			Active = false;
		}
	}


	void BULLET::moveY(float dy) {
		Py += dy;
	}

	void BULLET::draw() {
		if (!Active)
			return;

		image(Img, Px, Py);
	}

	void BULLET::deactivate() {
		Active = false;
	}

	bool BULLET::isActive() {
		return Active;
	}

	float BULLET::left() { return Px + 48; }
	float BULLET::right() { return Px + 80; }
	float BULLET::top() { return Py + 8; }
	float BULLET::bottom() { return Py + 68; }
}