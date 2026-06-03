#include "item.h"
#include "../../libOne/inc/graphic.h"
namespace GAME02 {
	void ITEM::create() {
		Img = loadImage("../main/assets\\game02\\kawaii.png");
	}
	
	void ITEM::init() {
		Alive = false;
		Vx = 5;
	}
	void ITEM::set(int x,int y) {
		Px = x;
		Py = y + 10;
		Alive = true;

	}
	void ITEM::update() {
			Py += Vx;
		if (Py > 1080) {
			Alive = false;
		}
	}

	float ITEM::left() { return Px - 28; }
	float ITEM::right() { return Px + 28; }
	float ITEM::top() { return Py - 28; }
	float ITEM::bottom() { return Py + 28; }
	bool ITEM::hit(PLAYER& p) {
		if (left() > p.right() ||
			right() < p.left() ||
			top() > p.bottom() ||
			bottom() < p.top()) {
			return false;
		}
		return true;
	}
	
	void ITEM::draw() {
		if (Alive) {
			image(Img, Px, Py);
		}
	}
}