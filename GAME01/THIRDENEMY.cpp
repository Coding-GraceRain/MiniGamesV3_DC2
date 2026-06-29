#include "THIRDENEMY.h"
namespace GAME01 {
	void THIRDENEMY::init(int IPx, int IPy) {
		isAlive = true;
		Px = map->Cell[IPx][IPy].Px;
		Py = map->Cell[IPx][IPy].Py;
		size = 50;
		n.HP = 20.0f;
		n.STR = 5.0f;
		n.DEF = 5.0f;
		n.INT = 5.0f;
		n.DEX = 5.0f;
		n.LUC = 0.0f;
		n.SIZ = 1;
		MaxHp = n.HP;
		rewardExp = 15;
	}
	void THIRDENEMY::draw() {
		if (!isAlive)return;
		textSize(size * n.SIZ);
		text("å³", Px, Py);
	}
}