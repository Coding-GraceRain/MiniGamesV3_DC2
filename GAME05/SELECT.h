#pragma once
#include"PLAYER.h"
namespace GAME05 {
	class SELECT{
	private:
		int SELECT_BLOCK_WIDTH = 0;
		int SELECT_BLOCK_HEIGHT = 0;
		bool STAGE1_select = 0;
		int STAGE1_positionX = 0;
		int STAGE1_positionY = 0;
		bool STAGE2_open = 0;
		bool STAGE2_select = 0;
		int STAGE2_positionX = 0;
		int STAGE2_positionY = 0;
		bool STAGE3_open = 0;
		bool STAGE3_select = 0;
		int STAGE3_positionX = 0;
		int STAGE3_positionY = 0;
		bool STAGE4_open = 0;
		bool STAGE4_select = 0;
		int STAGE4_positionX = 0;
		int STAGE4_positionY = 0;
		int mic_Image = 0;
	public:
		void INIT_for_SELECT();
		void DRAW_for_SELECT(class PLAYER* p_pointer);
		void MOVE_AREA(class PLAYER* p_pointer);
		void select_text();
		void DRAW_MIC();
		int STAGE_SELECT();
	};
}