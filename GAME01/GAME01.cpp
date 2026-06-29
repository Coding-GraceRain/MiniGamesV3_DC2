#include "../../libOne/inc/libOne.h"
#include "../MAIN/MAIN.h"
#include "GAME01.h"
#include"GAME.h"
namespace GAME01
{
	int GAME::create()
	{
		game = new GAME1(main());
		game->game01 = this;
		game->create();
		return 0;
	}
	void GAME::destroy()
	{
		delete game;
		game = nullptr;
	}
	void GAME::proc()
	{
		clear(0, 0, 64);
		game->proc();
	}
	void GAME::backToMenu() {
		main()->backToMenu();
	}
}
