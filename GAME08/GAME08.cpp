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
		Actors.push_back(Score = new SCORE(this));

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
		TitleFlag = true;

	}
	void GAME::proc()
	{
		if (TitleFlag)
		{
			clear(0,50,60);

			fill(255, 255, 0);
			textSize(80);
			textMode(BCENTER);
			text("PONG", 640, 250);

			textSize(40);
			fill(255);
			text("Player1 : A　　 D", 640, 450);
			text("Player2 : J　　 L", 640, 520);

			fill(0, 255, 0);
			text("ENTERを押してスタート", 640, 700);

			if (isTrigger(KEY_ENTER))
			{
				TitleFlag = false;
			}

			return;
		}
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
				textSize(125);
				fill(255, 0, 0);
				textMode(BCENTER);
				SCORE* score = (SCORE*)this->score();

				if (score->playerScore() >= 3)
				{
					text("PLAYER 1 WIN!", 960, 300);
				}
				else if (score->player2Score() >= 3)
				{
					text("PLAYER 2 WIN!", 960, 300);
				}
			}
		textSize(80);
		fill(255, 255, 0);
		text("PONG", 20, 30);
		if (isTrigger(KEY_ENTER)) {
			main()->backToMenu();
		}
	}
}
