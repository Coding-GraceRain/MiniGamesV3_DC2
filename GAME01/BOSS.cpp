#include "BOSS.h"
namespace GAME01 {
	void BOSS::init(int IPx, int IPy) {
		isAlive = true;
		Px = map->Cell[IPx][IPy].Px;
		Py = map->Cell[IPx][IPy].Py;
		size = 50;
		n.HP = 750.0f;
		n.STR = 140.0f;
		n.DEF = 50.0f;
		n.INT = 10.0f;
		n.DEX = 10.0f;
		n.LUC = 0.0f;
		n.SIZ = 1;
		MaxHp = n.HP;
		rewardExp = 200;
	}
	void BOSS::draw() {
		if (!isAlive)return;
		textSize(size * n.SIZ);
		text("‰¤", Px, Py);
	}
}