#include "BUTTON.h"
#include "GAME03.h"
#include "CONTAINER.h"
namespace GAME03
{
	BUTTON::BUTTON(class GAME* game) :
		CHARACTER(game) {
	}
	BUTTON::~BUTTON() {
	}
	void BUTTON::create() {
		Chara = game()->container()->data().buttonChara;
	}
	void BUTTON::appear(float x, float y, float vx, float vy) {
		Chara.hp = game()->container()->data().buttonChara.hp;
		Chara.x = x;
		Chara.y = y;
		Chara.img = game()->container()->data().buttonChara.img;
	}
	void BUTTON::update() {
		if (game()->map()->gimmickButton() == 1) {
			Chara.img = game()->container()->data().buttonChara.gimmickImg;
		}
	}
}