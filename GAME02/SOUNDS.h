#pragma once
namespace GAME02 {
	class SOUNDS
	{
	private:
		int TitleSound;
		int PlaySounds;
		int GameoverSound;
		int ClearSound;
		int ClickSound;
		int GetitemSound;
	public:
		void create();
		void titlesound();
		void playsound();
		void getitemsound();
		void playstopsound();
		void gameoversound();
		void clearsound();
		void clicksound();
	};
}

