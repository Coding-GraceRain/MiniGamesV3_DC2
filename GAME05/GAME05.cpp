#include "../../libOne/inc/libOne.h"
#include "../MAIN/MAIN.h"
#include "GAME.h"
#include "GAME05.h"
namespace GAME05
{
   
	int GAME::create()
	{
		GameCore = new GAME_;
		GameCore->run();

		
		return 0;
	}

	void GAME::destroy()
	{
		delete GameCore;
		GameCore = nullptr;
	}
	void GAME::proc()
	{
		GameCore->proc();


		
		fill(255, 255, 0);
		text("GAME05", 0, 100);
		fill(255);
		text("ENTERキーでメニューに戻る", 0, 1080);
		if (isTrigger(KEY_ENTER)) {
			main()->backToMenu();
		}
	}
}
