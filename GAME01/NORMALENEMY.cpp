#include "NORMALENEMY.h"
namespace GAME01
{
	void NORMALENEMY::init(int IPx, int IPy) {
		isAlive = true;
		Px = map->Cell[IPx][IPy].Px;
		Py = map->Cell[IPx][IPy].Py;
		size = 50;
		n.HP = 13.0f;
		n.STR = 3.0f;
		n.DEF = 3.0f;
		n.INT = 3.0f;
		n.DEX = 3.0f;
		n.LUC = 0.0f;
		n.SIZ = 1;
		MaxHp = n.HP;
		rewardExp = 10;
	}
	void NORMALENEMY::draw() {
		if (!isAlive)return;
		textSize(size * n.SIZ);
		text("狼", Px, Py);
	}
}