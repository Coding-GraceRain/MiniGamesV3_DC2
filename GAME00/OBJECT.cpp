#include"../../libOne/inc/graphic.h"
#include "OBJECT.h"
namespace GAME00
{
	void OBJECT::create() {
		Img = loadImage("../main/assets/game00/asiba_siro.png");
	}
	void OBJECT::init() {
		Px = 0.0f;
		Py = 1079.0f;
	}
	void OBJECT::moveY(float dy) {
		Py += dy;
	}
	void OBJECT::draw() {
		image(Img, Px, Py);
	}

	float OBJECT::left() { return Px; }
	float OBJECT::right() { return Px + 525; }
	float OBJECT::top() { return Py - 8; }
	float OBJECT::bottom() { return Py + 30; }
}