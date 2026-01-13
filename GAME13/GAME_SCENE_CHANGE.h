#pragma once

#include"GAME13.h"
namespace GAME13 {
	class GAME_SCENE {
		float TILE_SIZE = 300;
	public:
		const enum GAME_CHANGE {
			CHOOSE, MINESWEEPER, DASSYUTU
		};
		int now_game = 0;
		const enum scene {
			INIT, TITLE, OPTION, SELECT, PLAY
		};
		int game_state = 0;

		int GAME_SELECT();
	};
}