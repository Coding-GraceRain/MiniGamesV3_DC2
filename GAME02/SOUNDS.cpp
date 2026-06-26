#include "Sounds.h"
#include "../../libOne/inc/sound.h"

namespace GAME02 {
	void SOUNDS::create() {
		 //TitleSound=loadSound("../main\\assets\\game02\\");
		 PlaySound= loadSound("../main\\assets\\game02\\play.wav");
		 BossSound = loadSound("../main\\assets\\game02\\boss.wav");
		 GetitemSound = loadSound("../main\\assets\\game02\\getitem.wav");
		 GameoverSound=loadSound("../main\\assets\\game02\\gameover.wav");
		 //ClearSound=loadSound("../main\\assets\\game02\\");
		 ClickSound = loadSound("../main\\assets\\game02\\click.wav");
		 Boom = loadSound("../main\\assets\\game02\\boom.wav");
		 setsound();
	}
	void SOUNDS::setsound() {
		vol = -1600;
	}
	void SOUNDS::halfsound() {
		vol = -3400;
	}
	void SOUNDS::mutesound() {
		vol = -10000;
	}
	void SOUNDS::titlesound() {

	}
	
	void SOUNDS::playsound() {
		setVolume(PlaySound,vol);
		playLoopSound(PlaySound);
	}
	void SOUNDS::playstopsound() {
		stopSound(PlaySound);
	}
	void SOUNDS::bosssound() {
		setVolume(BossSound, vol);
		playLoopSound(BossSound);
	}
	void SOUNDS::bossStopSound() {
		stopSound(BossSound);
	}
	void SOUNDS::boom() {
		setVolume(Boom, vol);
		playSound(Boom);
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