#pragma once
namespace GAME04 {
	class ENEMY {
	public:
		float px = 1920 / 2;
		float py = 1080 - 930;
		float pr = 75 * 2;
		float w = 200;
		float h = 200;
		float vx = 10;
		float ofsY = 100;
		int hp = 20;

		void draw();
		void move();
		void mik();
		void fn();
	};
}