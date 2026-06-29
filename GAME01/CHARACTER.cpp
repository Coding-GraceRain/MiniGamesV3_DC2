#include "CHARACTER.h"
#include"GAME.h"
#include"PERSENT.h"
#include<string>
namespace GAME01
{
	void CHARACTER::create() {
		init();
	}
	void CHARACTER::init() {
		Px = 500;
		Py = 500;
		size = 50;
	}
	void CHARACTER::draw() {
		textSize(size * n.SIZ);
		text("試", Px, Py);
	}
	void CHARACTER::update() {
		n.HP = 10;
		if (isTrigger(KEY_D)) {
			Px += 1 * size;
		}
	}
	void CHARACTER::knockBack() {
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
	//こちらが真下にいる判定
	bool CHARACTER::enemyUp(CHARACTER* ME, CHARACTER* YOU, float step) {
		return (fabs(ME->Px - YOU->Px) < 0.1f) && (fabs((ME->Py - step) - YOU->Py) < 0.1f);
	}
	//こちらが真上にいる判定
	bool CHARACTER::enemyDawn(CHARACTER* ME, CHARACTER* YOU, float step) {
		return (fabs(ME->Px - YOU->Px) < 0.1f) && (fabs(YOU->Py - (ME->Py + step)) < 0.1f);
	}
	//こちらが真右にいる判定
	bool CHARACTER::enemyLeft(CHARACTER* ME, CHARACTER* YOU, float step) {
		return (fabs((YOU->Px) - (ME->Px - step)) < 0.1f) && (fabs(ME->Py - YOU->Py) < 0.1f);
	}
	//こちらが真左にいる判定
	bool CHARACTER::enemyRaight(CHARACTER* ME, CHARACTER* YOU, float step) {
		return (fabs((ME->Px + step) - (YOU->Px)) < 0.1f) && (fabs(ME->Py - YOU->Py) < 0.1f);
	}
	//こちらが真下にいる判定(壁)
	bool CHARACTER::objectUp(CHARACTER* ME, MAP* MAP) {
		if (ME->PCelly - 1 < 0)return true;
		return MAP->Cell[ME->PCellx][ME->PCelly - 1].type == 1;
	}
	//こちらが真上にいる判定(壁)
	bool CHARACTER::objectDawn(CHARACTER* ME, MAP* MAP) {
		if (ME->PCelly + 1 >= MAP->getRow()) return true;
		return MAP->Cell[ME->PCellx][(ME->PCelly) + 1].type == 1;
	}
	//こちらが真右にいる判定(壁)
	bool CHARACTER::objectLeft(CHARACTER* ME, MAP* MAP) {
		if (ME->PCellx - 1 < 0)return true;
		return MAP->Cell[(ME->PCellx) - 1][ME->PCelly].type == 1;
	}
	//こちらが真左にいる判定(壁)
	bool CHARACTER::objectRight(CHARACTER* ME, MAP* MAP) {
		if (ME->PCellx + 1 >= MAP->getCol()) return true; // 壁扱い
		return MAP->Cell[ME->PCellx + 1][ME->PCelly].type == 1;
	}
	void CHARACTER::attack(CHARACTER* ME, CHARACTER* YOU) {
		if (rand1000() < ME->n.LUC * 10)criticalHit = true;
		ME->knockTimer = game->getDelay();
		float step = ME->size * ME->n.SIZ;
		switch (ME->direction) {
		case 1:
			//半分進む
			ME->Py -= step / 2;
			if (criticalHit) {
				YOU->setHp(ME->n.STR * 2);
				std::string s = "critical!";
				textSize(20);
				for (int i = 0;i < 30;i++)text(s.c_str(), YOU->getPx(), YOU->getPy() - 60);
				ME->healHp(((ME->n.STR * 2) * (100.0f / (100.0f + YOU->n.DEF)) * (HPAbsorptionEffect / 100)));
			}
			else {
				YOU->setHp(ME->n.STR);
				ME->healHp((ME->n.STR * (100.0f / (100.0f + YOU->n.DEF)) * (HPAbsorptionEffect / 100)));
			}
			//戻る
			game->knockback(ME->direction, ME);
			break;
		case 2:
			//半分進む
			ME->Px -= step / 2;
			if (criticalHit) {
				YOU->setHp(ME->n.STR * 2);
				std::string s = "critical!";
				textSize(20);
				for (int i = 0;i < 30;i++)text(s.c_str(), YOU->getPx(), YOU->getPy() - 60);
				ME->healHp(((ME->n.STR * 2) * (100.0f / (100.0f + YOU->n.DEF)) * (HPAbsorptionEffect / 100)));
			}
			else {
				YOU->setHp(ME->n.STR);
				ME->healHp((ME->n.STR * (100.0f / (100.0f + YOU->n.DEF)) * (HPAbsorptionEffect / 100)));
			}
			//戻る
			game->knockback(ME->direction, ME);
			break;
		case 3:
			//半分進む
			ME->Py += step / 2;
			if (criticalHit) {
				YOU->setHp(ME->n.STR * 2);
				std::string s = "critical!";
				textSize(20);
				for (int i = 0;i < 30;i++)text(s.c_str(), YOU->getPx(), YOU->getPy() - 60);
				ME->healHp(((ME->n.STR * 2) * (100.0f / (100.0f + YOU->n.DEF)) * (HPAbsorptionEffect / 100)));
			}
			else {
				YOU->setHp(ME->n.STR);
				ME->healHp((ME->n.STR * (100.0f / (100.0f + YOU->n.DEF)) * (HPAbsorptionEffect / 100)));
			}
			//戻る
			game->knockback(ME->direction, ME);
			break;
		case 4:
			//半分進む
			ME->Px += step / 2;
			if (criticalHit) {
				YOU->setHp(ME->n.STR * 2);
				std::string s = "critical!";
				textSize(20);
				for (int i = 0;i < 30;i++)text(s.c_str(), YOU->getPx(), YOU->getPy() - 60);
				ME->healHp(((ME->n.STR * 2) * (100.0f / (100.0f + YOU->n.DEF)) * (HPAbsorptionEffect / 100)));
			}
			else {
				YOU->setHp(ME->n.STR);
				ME->healHp((ME->n.STR * (100.0f / (100.0f + YOU->n.DEF)) * (HPAbsorptionEffect / 100)));
			}
			//戻る
			game->knockback(ME->direction, ME);
			break;
		}
		criticalHit = false;
		ME->draw();
		ME->direction = 0;
	}
}


