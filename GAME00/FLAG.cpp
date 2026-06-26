#include"../../libOne/inc/graphic.h"
#include "FLAG.h"
namespace GAME00
{
	void FLAG::create() {
		Img = loadImage("../main/assets/game00/flag.png");
	}

	void FLAG::init() {
		Px = -20;
		Py = -4700;
	}

	void FLAG::moveY(float dy) {
		Py += dy;
	}

	void FLAG::draw(float scrollY) {
		image(Img, Px, Py + scrollY);
	}

	float FLAG::left() { return Px + 80; }
	float FLAG::right() { return Px + 80; }
	float FLAG::top(float scrollY) { return Py + scrollY; }
	float FLAG::bottom(float scrollY) { return Py + 120 + scrollY; }
}
