#include"ENEMY3.h"
#include "../../libOne/inc/graphic.h"
#include <ctime>
namespace GAME02 {
	
		void ENEMY3::create() {
			Img = loadImage("../main\\assets\\game02\\riri.png");
			srand((unsigned)time(NULL));
			Buf = 0;
		}
		void ENEMY3::init() {
			Px = 664 + rand() % 1227;
			Py = 30 + rand() % 400;
			Vx = 2.0f;
			Vy = 0.1f;
			Cum = 1000;
			Hp = 3;
			Delay = 0;
			Alive = true;
		}
		void ENEMY3::update() {
			if (Cum <= 0) {
				Rnd = rand() % 2;
				Cum = rand() % 300 + 300;
			}
			if (Rnd == 0) {
				Px += Vx;
				Cum -= 1;
			}
			else if (Rnd == 1) {
				Px -= Vx;
				Cum -= 1;

			}
			else
				Px += Vx;

			if (Px< width / 3 + 24 || Px>width - 24) { Vx *= -1; }
		}
		void ENEMY3::draw() {
			rectMode(CENTER);
			image(Img, Px, Py);
		}

		bool ENEMY3::drop() {
			return rand() % 100 < 15;
		}
		bool ENEMY3::harddrop() {
			return rand() % 100 < 5;
		}
		float ENEMY3::left() { return Px - 24.0f; }
		float ENEMY3::right() { return Px + 24.0f; }
		float ENEMY3::top() { return Py - 24.0f; }
		float ENEMY3::bottom() { return Py + 24.0f; }
		bool ENEMY3::hit(ENEMY3& ENEMY3) {
			if (left() <= ENEMY3.right() &&
				right() >= ENEMY3.left() &&
				top() <= ENEMY3.bottom() &&
				bottom() >= ENEMY3.top()) {
				return true;
			}
			return false;
		}
		bool ENEMY3::hit(ENEMY& enemy) {
			if (left() <= enemy.right() &&
				right() >= enemy.left() &&
				top() <= enemy.bottom() &&
				bottom() >= enemy.top()) {
				return true;
			}
			return false;
		}
	
}