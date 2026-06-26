#include "SEVENTHENEMY.h"
namespace GAME01 {
	void SEVENTHENEMY::init(int IPx, int IPy) {
		isAlive = true;
		Px = map->Cell[IPx][IPy].Px;
		Py = map->Cell[IPx][IPy].Py;
		size = 50;
		n.HP = 600.0f;
		n.STR = 100.0f;
		n.DEF = 35.0f;
		n.INT = 10.0f;
		n.DEX = 10.0f;
		n.LUC = 0.0f;
		n.SIZ = 1;
		MaxHp = n.HP;
		rewardExp = 75;
	}
	void SEVENTHENEMY::draw() {
		if (!isAlive)return;
		textSize(size * n.SIZ);
		text("冥", Px, Py);
	}
}