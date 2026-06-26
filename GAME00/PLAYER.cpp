#include "../../libOne/inc/graphic.h"
#include"../../libOne/inc/input.h"
#include"../../libOne/inc/window.h"
#include"../../libOne/inc/sound.h"
#include"PLAYER.h"
#include"ENEMY.h"
#include"OBJECT.h"
#include"OBJECT2.h"
namespace GAME00 {
	void PLAYER::create() {
		Img = loadImage("../main/assets/game00/player.png");
		JumpSe = loadSound("../main/assets/game00/jump.wav");
		DamageSe = loadSound("../main/assets//game00/damage.wav");
	}

	void PLAYER::init() {
		Px = 0;
		Py = height - 210;
		Vx = 300.0f;
		Vy = 0.0f;
		Gravity = 0.8f;
		JumpCount = 0;
		OnGround = false;
		MaxHp = 5;
		Hp = MaxHp;
		DamageTimer = 0.0f;
	}

	void PLAYER::update() {
		//移動
		if (isPress(KEY_D)) { Px += Vx * delta; }
		if (isPress(KEY_A)) { Px -= Vx * delta; }
		if (Px < 0)Px = 0;
		if (right() > width)Px = width - 125;
		if (Py > 1080)init();

		//ジャンプ
		if (isTrigger(KEY_SPACE) && JumpCount < Max_Jump) {
			setVolume(JumpSe, -2500);
			playSound(JumpSe);
			Vy = (JumpCount == 0) ? -17.0f : -15.0f;
			JumpCount++;
			OnGround = false;
		}

		Vy += Gravity;
		Py += Vy;

		if (DamageTimer > 0.0f) {
			DamageTimer -= delta;
			if (DamageTimer < 0.0f) {
				DamageTimer = 0.0f;
			}
		}
	}
	void PLAYER::moveY(float dy) {
		Py += dy;
	}

	void PLAYER::draw() {
		image(Img, Px, Py);

		if (DamageTimer > 0.0f) {
			fill(255, 0, 0, 100);
			rect(Px, Py, 70, 205);
		}
	}

	int PLAYER::getHp() {
		return Hp;
	}

	void PLAYER::damage(int value){
		if (DamageTimer > 0.0f) {
			return;
		}
		Hp -= value;
		if (Hp < 0)
			Hp = 0;

		DamageTimer = 1.0f;
		setVolume(DamageSe,-2500);
		playSound(DamageSe);
	}

	void PLAYER::respawn() {
		Px = 0;
		Py = height - 210;
		Vx = 300.0f;
		Vy = 0.0f;
		Gravity = 0.8f;
		JumpCount = 0;
		OnGround = false;
	}

	//プレイヤーの当たり判定
	float PLAYER::left() { return Px; }
	float PLAYER::right() { return Px + 125; }
	float PLAYER::top() { return Py; }
	float PLAYER::bottom() { return Py + 200; }


	//敵(ENEMY)との当たり判定
	bool PLAYER::hit(ENEMY& enemy) {
		if (left() > enemy.right() ||
			right() < enemy.left() ||
			top() > enemy.bottom() ||
			bottom() < enemy.top()) {
			return false;
		}
		return true;
	}

	//足場(OBJECT)との当たり判定
	bool PLAYER::hit(OBJECT& object) {
		if (left() > object.right() ||
			right() < object.left() ||
			top() > object.bottom() ||
			bottom() < object.top()) {
			return false;
		}
		return true;
	}

	//着地判定
	bool PLAYER::landOn(OBJECT& object) {
		float prevBottom = bottom() - Vy;

		if (prevBottom <= object.top() &&
			bottom() >= object.top() &&
			right() > object.left() &&
			left() < object.right()) {

			Py = object.top() - 200;
			Vy = 0;
			OnGround = true;
			JumpCount = 0;
			Vy = 0;
			return true;
		}
		return false;
	}

	//足場2(OBJECT2)との当たり判定
	bool PLAYER::hit(OBJECT2& object2) {
		if (left() > object2.right() ||
			right() < object2.left() ||
			top() > object2.bottom() ||
			bottom() < object2.top()) {
			return false;
		}
		return true;
	}

	bool PLAYER::hitCeiling(OBJECT2& object2) {
		if (Vy >= 0)return false;

		if (right() <= object2.left() || left() >= object2.right())
			return false;

		if (top() <= object2.bottom() && bottom() > object2.bottom()) {
			Py = object2.bottom();
			Vy = 0;
			return true;
		}
		return false;
	}

	bool PLAYER::hitSide(OBJECT2& object2) {
		if (Vy > 0)return false;

		if (bottom() <= object2.top() || top() >= object2.bottom())
			return false;

		if (Vx > 0 &&
			right() >= object2.left() &&
			left() < object2.left()) {

			Px = object2.left() - 125;
			return true;
		}

		if (Vx < 0 &&
			left() <= object2.right() &&
			right() > object2.right()) {

			Px = object2.right();
			return true;
		}
		return false;
	}

	bool PLAYER::landOn(OBJECT2& object2) {
		float prevBottom = bottom() - Vy;

		if (prevBottom <= object2.top() &&
			bottom() >= object2.top() &&
			right() > object2.left() &&
			left() < object2.right()) {

			Py = object2.top() - 200;
			Vy = 0;
			OnGround = true;
			JumpCount = 0;
			Vy = 0;
			return true;
		}
		return false;
	}

	bool PLAYER::hit(BULLET& bullet) {

		if (!bullet.isActive())
			return false;

		if (left() > bullet.right() ||
			right() < bullet.left() ||
			top() > bullet.bottom() ||
			bottom() < bullet.top()) {
			return false;
		}
		return true;
	}

	bool PLAYER::isDead() {
		return Hp <= 0;
	}


	bool PLAYER::isDamage() {
		return DamageTimer > 0.0f;
	}

	void PLAYER::saveStartPos() {
		StartX = Px;
		StartY = Py;
	}

	void PLAYER::returnToStart() {
		Px = StartX;
		Py = StartY;
		Vy = 0.0f;
		OnGround = false;
	}

	void PLAYER::destroy() {
		releaseSound(JumpSe);
		releaseSound(DamageSe);
	}
}