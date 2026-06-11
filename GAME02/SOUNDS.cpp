#include "Sounds.h"
#include "../../libOne/inc/sound.h"

namespace GAME02 {
	void SOUNDS::create() {
		 //TitleSound=loadSound();
		 PlaySounds= loadSound("../main\\assets\\game02\\urusai.wav");
		 GetitemSound = loadSound("../main\\assets\\game02\\getitem.wav");
		 GameoverSound=loadSound("../main\\assets\\game02\\gameover.wav");
		 ClearSound;
		 ClickSound = loadSound("../main\\assets\\game02\\click.wav");
	}
	void SOUNDS::titlesound() {

	}
	void SOUNDS::playsound() {
		setVolume(PlaySounds,-5000);
		playLoopSound(PlaySounds);
	}
	void SOUNDS::playstopsound() {
		stopSound(PlaySounds);
	}
	void SOUNDS::getitemsound() {
		setVolume(GetitemSound, -5200);
		playSound(GetitemSound);
	}
	void SOUNDS::gameoversound() {
		setVolume(GameoverSound, -5200);
		playSound(GameoverSound);
	}
	void SOUNDS::clearsound() {

	}
	void SOUNDS::clicksound() {
		playSound(ClickSound);
	}

}