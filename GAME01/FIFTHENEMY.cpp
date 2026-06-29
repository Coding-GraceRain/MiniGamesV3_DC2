#include "FIFTHENEMY.h"
namespace GAME01 {
	void FIFTHENEMY::init(int IPx, int IPy) {
		isAlive = true;
		Px = map->Cell[IPx][IPy].Px;
		Py = map->Cell[IPx][IPy].Py;
		size = 50;
		n.HP = 100.0f;
		n.STR = 25.0f;
		n.DEF = 20.0f;
		n.INT = 10.0f;
		n.DEX = 10.0f;
		n.LUC = 0.0f;
		n.SIZ = 1;
		MaxHp = n.HP;
		rewardExp = 20;
	}
	void FIFTHENEMY::draw() {
		if (!isAlive)return;
		textSize(size * n.SIZ);
		text("ŒF", Px, Py);
	}
}