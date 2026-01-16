#include "Board.h"
#include "GAME08.h"
#include "../MAIN/MAIN.h"
#include "../../libOne/inc/libOne.h"



namespace GAME08
{
	using namespace GAME08;

	GAME::GAME(MAIN* main)
		: GAME_BASE(main)
		, board()
	{
	}

	int GAME::create()
	{
		board = new Board();
		return 0;
	}

	void GAME::destroy()
	{
		delete board;
		board = nullptr;
	}

	void GAME::proc()
	{
		clear(0, 0, 0);

		board->update();
		board->draw();

		// –ß‚éˆ—
		fill(255);
		textSize(30);
		text("ENTER : ƒƒjƒ…[‚É–ß‚é", 50, 1050);

		if (isTrigger(KEY_ENTER)) {
			main()->backToMenu();
		}

	}
}