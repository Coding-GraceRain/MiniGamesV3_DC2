#include "BULLET.h"
#include "../../libOne/inc/mathUtil.h"

namespace GAME02 {
		void BULLET::create() {
			Img = loadImage("../main\\assets\\game02\\Bullet.png");
			
		}
		void BULLET::init() {
			Vy = -10.0f;
			Alive = false;
		}
		void BULLET::shoot(int x,int y) {
			Bx = x;
			By = y;
			Alive = true;
			
		}
		void BULLET::update(){
			if (!Alive) {
				return;
			}

			By += Vy;
			Bx += Vx;
			if (Delay > 0) {
				Delay -= 0.1f;
			}

			if (By < 0) {
				Alive = false;
			}
			
		}
		void BULLET::draw() {
			rectMode(CENTER);
			if (Alive) {
				image(Img, Bx, By);
			}
		}
		float BULLET::left() { return Bx - 15.0f; }
		float BULLET::right() { return Bx + 15.0f; }
		float BULLET::top() { return By - 15.0f; }
		float BULLET::bottom() { return By + 15.0f; }

		bool BULLET::hit(ENEMY& enemy) {
			if (left() < enemy.right() &&
				right() > enemy.left() &&
				top() < enemy.bottom() &&
				bottom() > enemy.top()) {
				return true;
			}
			return false;
		}
		bool BULLET::hit(ENEMY3& enemy) {
			if (left() < enemy.right() &&
				right() > enemy.left() &&
				top() < enemy.bottom() &&
				bottom() > enemy.top()) {
				return true;
			}
			return false;
		}
		
}