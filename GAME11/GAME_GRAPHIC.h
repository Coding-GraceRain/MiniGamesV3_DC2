#pragma once
#include "GAME11.h"
#include"PLAYER_and_NPC.h"
namespace GAME11 {
	class MAP {
		const int TILE_SIZE = 32;
		float BUG_X = 0;
		float BUG_Y = 0;

	public:
		void RANDOM_SET();
		void MOVE_CAMERA(PLAYER* player);
		//void RANDOM_SET();
		void Like_a_BUG(int percent, int color, int pattern);
		void DRAW_BUG();
		int DRAW_TEXT();
	};


}