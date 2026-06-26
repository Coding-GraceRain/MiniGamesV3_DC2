#include "SIXTHENEMY.h"
namespace GAME01 {
	void SIXTHENEMY::init(int IPx, int IPy) {
		isAlive = true;
		Px = map->Cell[IPx][IPy].Px;
		Py = map->Cell[IPx][IPy].Py;
		size = 50;
		n.HP = 175.0f;
		n.STR = 40.0f;
		n.DEF = 25.0f;
		n.INT = 10.0f;
		n.DEX = 10.0f;
		n.LUC = 0.0f;
		n.SIZ = 1;
		MaxHp = n.HP;
		rewardExp = 35;
	}
	void SIXTHENEMY::draw() {
		if (!isAlive)return;
		textSize(size * n.SIZ);
		text("蝿", Px, Py);
	}
}