#pragma once
#include "../../libOne/inc/libOne.h"

namespace GAME04 {
	
	class PLAYER {
	public:
		int ing = 0;
		float px = 1920 / 2;
		float py = 1080 - 150;
		float pr = 25 * 2;
		float w = 100;
		float h = 200;
		float vx = 15;
		float ofsY = -100;
		int hp = 10;
		void move();
		void loadImage(const char* filepath);

		void ku();
		void ef();
		void draw();

	};

}