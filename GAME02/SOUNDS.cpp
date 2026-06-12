#include "Sounds.h"
#include "../../libOne/inc/sound.h"

namespace GAME02 {
	void SOUNDS::create() {
		 //TitleSound=loadSound();
		 PlaySounds= loadSound("../main\\assets\\game02\\play.wav");
		 GetitemSound = loadSound("../main\\assets\\game02\\getitem.wav");
		 GameoverSound=loadSound("../main\\assets\\game02\\gameover.wav");
		 ClearSound;
		 ClickSound = loadSound("../main\\assets\\game02\\click.wav");
		 setsound();
	}
	void SOUNDS::setsound() {
		vol = -2200;
	}
	void SOUNDS::halfsound() {
		vol = -3600;
	}
	void SOUNDS::mutesound() {
		vol = -10000;
	}
	void SOUNDS::titlesound() {

	}
	void SOUNDS::playsound() {
		setVolume(PlaySounds,vol);
		playLoopSound(PlaySounds);
	}
	void SOUNDS::playstopsound() {
		stopSound(PlaySounds);
	}
	void SOUNDS::getitemsound() {
		setVolume(GetitemSound, vol);
		playSound(GetitemSound);
	}
	void SOUNDS::gameoversound() {
		setVolume(GameoverSound, vol);
		playSound(GameoverSound);
	}
	void SOUNDS::clearsound() {

	}
	void SOUNDS::clicksound() {
		setVolume(ClickSound, vol);
		playSound(ClickSound);
	}
	
}