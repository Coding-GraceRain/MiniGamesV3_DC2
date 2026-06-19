#pragma once
namespace GAME02 {
	class SOUNDS
	{
	private:
		int TitleSound;
		int PlaySound;
		int GameoverSound;
		int ClearSound;
		int ClickSound;
		int GetitemSound;
		int BossSound;
	public:
		int vol;
		void create();
		void titlesound();
		void playsound();
		void playstopsound();
		void bosssound();
		void bossStopSound();
		void getitemsound();
		void gameoversound();
		void clearsound();
		void clicksound();
		void setsound();
		void halfsound();
		void mutesound();
	};
}

