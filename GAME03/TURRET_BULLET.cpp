#include "TURRET_BULLET.h"
#include "GAME03.h"
#include "CONTAINER.h"
namespace GAME03
{
	void TURRET_BULLET::create() {
		Chara = game()->container()->data().turretBulletChara;
	}
	void TURRET_BULLET::appear(float x, float y, float vx, float vy) {
		Chara.hp = game()->container()->data().turretBulletChara.hp;
		Chara.x = x;
		Chara.y = y;
		Chara.vy = vy;
	}
	void TURRET_BULLET::update() {
		Chara.y += Chara.vy * (Chara.speed * delta);
		if (game()->map()->collisionCharaRect(wLeft(), wTop(), wRight(), wBottom()) ||
			Chara.y < -game()->map()->chipSize() ||
			Chara.y > height ) {
			Chara.hp = 0;
		}
	}
}