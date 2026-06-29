#include "WEAKENEMY.h"
namespace GAME01
{
	void WEAKENEMY::init(int IPx, int IPy) {
		isAlive = true;
		Px = map->Cell[IPx][IPy].Px;
		Py = map->Cell[IPx][IPy].Py;
		size = 50;
		n.HP = 10.0f;
		n.STR = 1.0f;
		n.DEF = 1.0f;
		n.INT = 1.0f;
		n.DEX = 1.0f;
		n.LUC = 0.0f;
		n.SIZ = 1;
		MaxHp = n.HP;
		rewardExp = 5;
	}
	void WEAKENEMY::draw() {
		if (!isAlive)return;
		textSize(size * n.SIZ);
		text("çú", Px, Py);
	}
}