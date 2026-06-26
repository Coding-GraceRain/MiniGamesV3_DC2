#include "../../libOne/inc/graphic.h"
#include "OBJECT2.h"
namespace GAME00
{
	void OBJECT2::create() {
		Img = loadImage("../main/assets/game00/asiba1.png");
		FallImg = loadImage("../main/assets/game00/asiba_fall.png");
	}
	void OBJECT2::init(float x, float y, bool falling, bool move) {
		Px = x;
		Py = y;
		StartX = x;
		StartY = y;
		IsFall = falling;
		IsFalling = false;
		FallSpeed = 0.0f;
		if (falling) {
			IsFalling = false;
		}
		IsMove = move;
		MoveDir = 1;
		MoveSpeed = 2.0f;
	}
	void OBJECT2::startfall() {
		if (!IsFalling) {
			IsFalling = true;
			FallSpeed = 0.0f;
		}
	}
	void OBJECT2::startmove() {
		//移動床
		if (!IsMove)return;
		Px += MoveSpeed * MoveDir;
		//移動範囲
		if (Px > 700) MoveDir = -1;  //左に動く
		if (Px < 450) MoveDir = 1;   //右に動く
	}
	void OBJECT2::update() {
		//落下床
		if (IsFalling) {
			FallSpeed += 0.6f;
			Py += FallSpeed;

			if (Py > height + 2000) {
				Px = StartX;
				Py = StartY;
				IsFalling = false;
				FallSpeed = 0.0f;
			}
		}
	}
	void OBJECT2::moveY(float dy) {
		Py += dy;
		StartY += dy;
	}
	void OBJECT2::draw() {
		if (IsFall) {
			image(FallImg, Px, Py);
		}
		else {
			image(Img, Px, Py);
		}
	}

	float OBJECT2::left() { return Px + 65; }
	float OBJECT2::right() { return Px + 170; }
	float OBJECT2::top() { return Py - 9; }
	float OBJECT2::bottom() { return Py + 30; }


	//----------------------------------------------------------------
	//デバッグ
	/*
		void OBJECT2::drawDebugNum(int num){
			fill(255,0,0);
			textSize(20);
			text(num,Px,Py);
		}
	*/
	//----------------------------------------------------------------
}