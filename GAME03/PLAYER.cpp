#include "PLAYER.h"
#include"CONTAINER.h"
#include"GAME03.h"
namespace GAME03
{
	PLAYER::PLAYER(class GAME* game):
	CHARACTER(game){
	}
	void PLAYER::create(){
		Chara = game()->container()->data().playerChara;
		Player = game()->container()->data().player;
	}
	void PLAYER::appear(float x, float y, float vx, float vy) {
		Chara.hp = game()->container()->data().playerChara.hp;
		Chara.x = x;
		Chara.y = y;
		Player.jumpFlag = 0;
		State = STATE::STRUGGLING;
	}
	void PLAYER::update() {
		Move();
		CollisionWithMap();
		CheckState();
	}
	void PLAYER::Move() {
		if (Player.jumpFlag == 0 && isTrigger(KEY_W)) {
			Chara.vy = Player.initVy;
			Player.jumpFlag = 1;
		}
		if (Player.jumpFlag == 1) {
			Chara.vy += Player.gravity * delta;
			Chara.y += Chara.vy * 60 * delta;
		}

		Chara.vx = 0.0f;
		if (isPress(KEY_D)) {
			Chara.vx = Chara.speed * delta;
		}
		if (isPress(KEY_A)) {
			Chara.vx = -Chara.speed * delta;
		}
		Player.curWx = Chara.x;

		if (Chara.vx != 0.0f) {
			Chara.x += Chara.vx;
		}
	}

	void PLAYER::CollisionWithMap(){
		MAP* map = game()->map();
		if (map->collisionCharaRight(Chara.x, Chara.y)) {
			Chara.x = Player.curWx;
		}
		else {
			if (map->collisionCharaLeft(Chara.x, Chara.y) ||
				Chara.x < 0) {
				Chara.x = Player.curWx;
			}
		}
		if (map->collisionCharaTop(Chara.x, Chara.y)) {
			Chara.vy = Player.gravity;
		}

		if (map->collisionCharaBottom(Player.curWx, Chara.y)) {
			Player.jumpFlag = 0;
			Chara.vy = 0.0f;
			Chara.y = (int)Chara.y / map->chipSize() * (float)map->chipSize();
		}
		else {
			Player.jumpFlag = 1;
		}
	}
	void PLAYER::CheckState() {
		if (Chara.y > height + game()->map()->chipSize()) {
			State = STATE::FALL;
			Chara.hp = 0;
			return;
		}
		if (Chara.x > width) {
			State = STATE::SURVIVED;
			Chara.hp = 0;
		}
	}
	void PLAYER::damage() {
		if (Chara.hp > 0) {
			Chara.hp--;
			if (Chara.hp == 0) {
				State = STATE::DIED;
				Chara.vy = Player.initVy;
			}
		}
	}
	bool PLAYER::died() {
		if (State == STATE::DIED) {
			Chara.vy += Player.gravity * delta;
			Chara.y += Chara.vy * 60 * delta;
			draw();
			return true;
		}
		else if (State == STATE::FALL) {
			return true;
		}
		return false;
	}
	bool PLAYER::survived() {
		return State == STATE::SURVIVED;
	}
}