#pragma once
//#include"GAME14.cpp"
#include"GAME14.h"

namespace GAME14 {
	class GAME_SCENE {
		float TILE_SIZE = 300;
	public:
		const enum GAME_CHANGE {
			CHOOSE,HIRAGANA,EXPLOIT
		};
		int now_game = 0;
		const enum scene {
			INIT, TITLE, OPTION, SELECT, PLAY
		};
		int game_state = 0;
		const enum hira_stage {
			stage1,stage2,stage3,stage4,stage5
		};
		int now_stage = 0;

		int change_stage = 0;
		int GAME_SELECT();
	};
}