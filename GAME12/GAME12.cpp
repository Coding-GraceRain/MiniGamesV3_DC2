#include "../../libOne/inc/libOne.h"
#include "../MAIN/MAIN.h"
#include "GAME12.h"
namespace GAME12
{
	int GAME::create()
	{
		mario = new MARIO;
		return 0;
	}

	void GAME::destroy()
	{
		delete mario;
	}

	void GAME::proc()
	{
		mario->game_console();
		if (mario->Back_Scene == true) {
			main()->backToMenu();
		}
	}
}
