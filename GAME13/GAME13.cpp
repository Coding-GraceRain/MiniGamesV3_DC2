#include "../../libOne/inc/libOne.h"
#include "../MAIN/MAIN.h"
#include "GAME13.h"
namespace GAME13
{
	int GAME::create()
	{
		game_scene = new  GAME_SCENE;
		minesweeper = new MINESWEEPER;
		dassyutu = new DASSYUTU;
		return 0;
	}

	void GAME::destroy()
	{
		delete game_scene;
		delete minesweeper;
		delete dassyutu;

	}

	void GAME::proc()
	{
		clear(0);
		if (game_scene->now_game == game_scene->CHOOSE) {
			textMode(BOTTOM);
			game_scene->GAME_SELECT();
			//clear(0, 0, 64);
			textSize(50);
			fill(255, 255, 0);
			text("GAME13", 0, 100);
			fill(255);
			text("ENTERキーでメニューに戻る", 0, 1080);
			if (isTrigger(MOUSE_LBUTTON) == 1 && game_scene->GAME_SELECT() == 1) {
				game_scene->now_game = game_scene->MINESWEEPER;
			}
			if (isTrigger(MOUSE_LBUTTON) == 1 && game_scene->GAME_SELECT() == 2) {
				game_scene->now_game = game_scene->DASSYUTU;
			}
			if (isTrigger(KEY_ENTER)) {
				main()->backToMenu();
			}
		}
		if (game_scene->now_game == game_scene->MINESWEEPER) {
			minesweeper->Game_console();
			if (minesweeper->Sent_Back_Scene() == true) {
				game_scene->now_game = game_scene->CHOOSE;
			}
		}
		if (game_scene->now_game == game_scene->DASSYUTU) {
			dassyutu->Game_console();
			if (dassyutu->Sent_Back_Scene() == true) {
				game_scene->now_game = game_scene->CHOOSE;
			}
		}
	}
}
