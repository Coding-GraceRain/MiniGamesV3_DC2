#include "../../libOne/inc/libOne.h"
#include "../MAIN/MAIN.h"
#include "GAME05.h"
#include"GAME_STRUCT.h"
namespace GAME05 {
	void GAME_STRUCT::Music_Change() {
		if (isTrigger(KEY_M)) {
			music_onoff = 1 - music_onoff;
		}
	}
}