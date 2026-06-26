#include "CHARACTER.h"
#include "../../libOne/inc/libOne.h"
namespace GAME03
{
	CHARACTER::CHARACTER(GAME* game) :
		GAME_OBJECT(game) {
	}
	void CHARACTER::create() {
	}
	void CHARACTER::init() {
		Chara.hp = 0;
	}
	void CHARACTER::appear(float x, float y, float vx, float vy) {
		Chara.x = x;
		Chara.y = y;
		Chara.hp = 1;
	}
	void CHARACTER::update() {
	}
	void CHARACTER::draw() {
		image(Chara.img, Chara.x, Chara.y);
	}
	void CHARACTER::damage() {
		if (Chara.hp > 0) {
			Chara.hp--;
		}
	}
}