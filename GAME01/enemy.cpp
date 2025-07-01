#include "enemy.h"
#include "../../libOne/inc/libOne.h"
#include "../MAIN/MAIN.h"
#include "GAME01.h"
namespace GAME01 {
	void ENEMY::move() {
		EposX = EposX - 1.0f;
	}
	void ENEMY::draw() {
		image(img, EposX, EposY);
	}
}