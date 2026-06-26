#include "CHARACTER_MANAGER.h"
#include "GAME03.h"
#include "CONTAINER.h"
#include "CHARACTER.h"
#include "TURRETS.h"
#include "TURRET_BULLET.h"
#include "BUTTON.h"
namespace GAME03
{
	CHARACTER_MANAGER::CHARACTER_MANAGER(GAME* game) :
		GAME_OBJECT(game) {
	}
	CHARACTER_MANAGER::~CHARACTER_MANAGER() {
		for (int i = 0; i < Total; i++) {
			delete Characters[i];
		}
		delete[] Characters;
	}
	void CHARACTER_MANAGER::create() {
		CharaMng = game()->container()->data().charaMng;

		Total = 0;
		Total += CharaMng.numPlayers;
		Total += CharaMng.numTurrets;
		Total += CharaMng.numTurretBullets;
		Total += CharaMng.numButton;
		Characters = new CHARACTER * [Total];

		Player = new PLAYER(game());
		int i, j = 0;
		for (i = 0; i < CharaMng.numPlayers; i++)		Characters[j++] = Player;
		for (i = 0; i < CharaMng.numTurrets; i++)		Characters[j++] = new TURRETS(game());
		for (i = 0; i < CharaMng.numTurretBullets; i++) Characters[j++] = new TURRET_BULLET(game());
		for (i = 0; i < CharaMng.numButton; i++)		Characters[j++] = new BUTTON(game());


		for (int i = 0; i < Total; i++) {
			Characters[i]->create();
		}
	}
	void CHARACTER_MANAGER::init() {
		for (int i = 0; i < Total; i++) {
			Characters[i]->init();
		}
	}
	void CHARACTER_MANAGER::appear(char charaId, float x, float y, float vx, float vy) {
		for (int i = 0; i < Total; i++) {
			if (Characters[i]->charaId() == charaId) {
				if (Characters[i]->hp() <= 0) {
					Characters[i]->appear(x, y, vx, vy);
					break;
				}
			}
		}
	}
	void CHARACTER_MANAGER::update() {
		for (int i = 0; i < Total; i++) {
			if (Characters[i]->hp() > 0) {
				Characters[i]->update();
			}
		}
		for (int i = 0; i < Total - 1; i++) {
			if (Characters[i]->hp() == 0) {
				continue;
			}
			for (int j = i + 1; j < Total; j++) {
				if (Characters[j]->hp() == 0) {
					continue;
				}
				if (Characters[i]->wLeft() < Characters[j]->wRight() &&
					Characters[j]->wLeft() < Characters[i]->wRight() &&
					Characters[i]->wTop() < Characters[j]->wBottom() &&
					Characters[j]->wTop() < Characters[i]->wBottom()) {
					if (Characters[i]->groupId() == Characters[j]->groupId()) {
						game()->map()->gimmick();
						continue;
					}
					Characters[i]->damage();
					Characters[j]->damage();
				}
			}
		}
	}
	void CHARACTER_MANAGER::draw() {
		for (int i = 0; i < Total; i++) {
			if (Characters[i]->hp() > 0) {
				Characters[i]->draw();
			}
		}
	}
}