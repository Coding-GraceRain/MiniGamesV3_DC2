#include "../../libOne/inc/libOne.h"
#include "../MAIN/MAIN.h"
#include"../MENU/MENU.h"
#include "GAME08.h"
#include"ACTOR.h"
#include"COURT.h"
#include"PLAYER.h"
#include"BALL.h"
#include"PLAYER2.h"
#include"SCORE.h"

namespace GAME08
{
	int GAME::create()
	{
		Actors.push_back(Court = new COURT(this));
		Actors.push_back(Player = new PLAYER(this));
		Actors.push_back(Ball = new BALL(this));
		Actors.push_back(Player2 = new PLAYER2(this));
		Actors.push_back(new SCORE(this));

		Init();

		return 0;
	}
	
	void GAME::destroy()
	{
		for (ACTOR* actor : Actors)
		{
			delete actor;
		}
	}

	void GAME::Init()
	{
		for(ACTOR*actor:Actors){ actor->init();}
		Playing = true;

	}
	void GAME::proc()
	{
		clear(0, 0, 64);

		if (Playing) {
			for (ACTOR* actor : Actors)
			{
				actor->update();
			}
		}
			for (ACTOR* actor : Actors)
			{
				actor->draw();
			}
			if (!Playing)
			{
				textSize(425);
				fill(255, 0, 0);
				textMode(BCENTER);
				text("YOU LOSE", 200, 540);
			}
		textSize(80);
		fill(255, 255, 0);
		text("PON", 10, 100);
		if (isTrigger(KEY_ENTER)) {
			main()->backToMenu();
		}
	}
}
