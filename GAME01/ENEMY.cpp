#include "ENEMY.h"
#include"GAME.h"
#include<string>
#include<cmath>
namespace GAME01
{
	ENEMY::~ENEMY() {
		player = nullptr;
	}
	void ENEMY::init(int IPx, int IPy) {
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
		rewardExp = 1;
		MaxHp = n.HP;
	}
	void ENEMY::draw() {
		if (!isAlive)return;
		textSize(size * n.SIZ);
		text("仮", Px, Py);
	}
	void ENEMY::update() {
		
		attacking = false;
		if (knockTimer > 0) return;
		if (acted)return;
		if (n.HP <= 0) {
			isAlive = false;
			game->enemyTCrQ();
			return;
		}
		if (!isAlive)return;
		//行動回数をいじくるやつ
		float Action = std::ceil(n.DEX / 10);
		float step = (size * n.SIZ);

		if (!game->enemyTrunFlag) return;
		float dx = player->getPx() - Px;
		float dy = player->getPy() - Py;

		if (abs(dx) > abs(dy)) {
			if (dx > 0) {
				if (enemyRaight(this, player, getstep()))actRIGHT();
				else if (canMoveRIGHT())actRIGHT();
				else if (dy > 0 && canMoveDOWN())actDOWN();
				else if (canMoveUP())actUP();
				else if (canMoveLEFT())actLEFT();
			}
			else {
				if (enemyLeft(this, player, getstep()))actLEFT();
				else if (canMoveLEFT())actLEFT();
				else if (dy > 0 && canMoveDOWN())actDOWN();
				else if (canMoveUP())actUP();
				else if (canMoveRIGHT())actRIGHT();
			}
		}
		else {
			if (dy > 0) {
				if (enemyDawn(this, player, getstep()))actDOWN();
				else if (canMoveDOWN())actDOWN();
				else if (dx > 0 && canMoveRIGHT())actRIGHT();
				else if (canMoveLEFT())actLEFT();
				else if (canMoveUP())actUP();
			}
			else {
				if (enemyUp(this, player, getstep()))actUP();
				else if (canMoveUP())actUP();
				else if (dx > 0 && canMoveRIGHT())actRIGHT();
				else if (canMoveLEFT())actLEFT();
				else if (canMoveDOWN())actDOWN();
			}
		}
		if (knockTimer == 0) {
			PCellx = (int)std::round((Px - map->getIPx()) / step);
			PCelly = (int)std::round((Py - map->getIPy()) / step);
			Px = map->getIPx() + PCellx * step;
			Py = map->getIPy() + PCelly * step;
		}
	}
	void ENEMY::statusdraw() {
	}
	void ENEMY::move() {
		switch (direction) {
		case 1:
			Py -= map->getGridSize();
			break;
		case 2:
			Px -= map->getGridSize();
			break;
		case 3:
			Py += map->getGridSize();
			break;
		case 4:
			Px += map->getGridSize();
			break;
		}
		acted = true;
		direction = 0;
	}
	void ENEMY::knockBack() {
		Px += knockVx;
		Py += knockVy;
		knockTimer--;
		game->knockbackFlag = true;
		if (knockTimer == 0) {
			float step = size * n.SIZ;

			PCellx = (int)std::round((Px - map->getIPx()) / step);
			PCelly = (int)std::round((Py - map->getIPy()) / step);

			Px = map->getIPx() + PCellx * step;
			Py = map->getIPy() + PCelly * step;

			knockVx = 0;
			knockVy = 0;
		}
	}
	void ENEMY::actUP() {
		bool hitenemy = false;
		direction = 1;
		if (!attacking && enemyUp(this, player, getstep())) {
			hitenemy = true;
			attack(this, player);
			attacking = true;
			acted = true;
		}
		if (!hitenemy) { move(); }
	}
	void ENEMY::actLEFT() {
		std::string s = "this:" + std::to_string((int)this) + "STR" + std::to_string(n.STR);
		bool hitenemy = false;
		direction = 2;
		if (!attacking && enemyLeft(this, player, getstep())) {
			hitenemy = true;
			attack(this, player);
			attacking = true;
			acted = true;
		}
		if (!hitenemy) { move(); }
	}
	void ENEMY::actDOWN() {
		bool hitenemy = false;
		direction = 3;
		if (!attacking && enemyDawn(this, player, getstep())) {
			hitenemy = true;
			attack(this, player);
			attacking = true;
			acted = true;
		}
		if (!hitenemy) { move(); }
	}
	void ENEMY::actRIGHT() {

		bool hitenemy = false;
		direction = 4;
		if (!attacking && enemyRaight(this, player, getstep())) {
			hitenemy = true;
			attack(this, player);
			attacking = true;
			acted = true;
		}
		if (!hitenemy) { move(); }
	}
	bool ENEMY::canMoveUP() {
		return !game->occupied(PCellx, PCelly - 1, this);
	}
	bool ENEMY::canMoveLEFT() {
		return !game->occupied(PCellx - 1, PCelly, this);
	}
	bool ENEMY::canMoveDOWN() {
		return !game->occupied(PCellx, PCelly + 1, this);
	}
	bool ENEMY::canMoveRIGHT() {
		return !game->occupied(PCellx + 1, PCelly, this);
	}
	
}