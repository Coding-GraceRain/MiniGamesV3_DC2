#include "../../libOne/inc/libOne.h"
#include "../MAIN/MAIN.h"
#include "GAME06.h"
#include <ctime>
namespace GAME06
{
	
	int GAME::create()
	{
		srand((unsigned int)time(NULL));
		Sound = loadSound("../../MiniGamesV3_DC2/MAIN/assets/game06/\\start.wav");
		//Sound2 = loadSound("../../MiniGamesV3_DC2/MAIN/assets/game06/\\clear.wav");
		player.create();
		item.create();
		back.create();
		return 0;
	}
	void GAME::init()
	{
		
		text("ENTERでMENU", 0, height);
		text("SPACEで次へ", 0, height-50);
		textSize(150);
		text("TITLE",width/2-100, height / 2);
		State = TITLE;
		player.init();
		item.init();
		if (isTrigger(KEY_SPACE))
		{
			State = EXP;
		}
	}
	void GAME::exp()
	{
		text("Dキーで右移動", 0, height - 150);
		text("Aキーで左移動", 0, height - 100);
		text("SPACEで始める", 0, height - 50);
		textSize(100);
		text("時間が0になったら終わり", 400, height / 2);
		textSize(150);
		text("操作説明", width / 2-300 , 200);
		State = EXP;
		if (isTrigger(KEY_SPACE))
		{
			playSound(Sound);
			State = PLAY;

		}

	}
	void GAME::update() 
	{
		hideCursor();
		printSize(50);
		textSize(50);
		back.draw();
		text((let)"SCORE:" + player.Score, 0, 50);
		text((let)"残り時間:" + player.Timer, 0, 100);
		text((let)"マイナス" + player.Get, 0, 150);
		player.update();
		player.draw();
		item.update();
		item.draw();
		player.hit(item);
		if (player.Timer > 0)
		{
			//player.Timer -= DeltaTime;
			player.Timer--;
		}
		if (20<=player.Score) 
		{
			//playSound(Sound2);
			player.Score -= player.Get;
			player.Score *= player.Timer;
			State = RESULT;
		}
		else if (player.Timer <= 0)
		{
			player.Timer = 0;
			State = RESULT;
		}
	}
	
	
	void GAME::result()
	{
		textSize(150);
		text("RESULT", width / 2-100, height / 4);
		textSize(50);
		text("R KEYでPLAY", 0, height-50);
		text("T KEYでTITLE", 0,height);
		player.score();

		if (isTrigger(KEY_R))
		{
			player.init();
			item.init();
			State = PLAY;
		}
		else if (isTrigger(KEY_T))
		{
			State = TITLE;
		}
	}
	void GAME::destroy()
	{

	}

	void GAME::proc()
	{
		clear(0, 0, 64);
		textSize(50);
		fill(255, 255, 0);
		text("GAME06", 0, 0);
		fill(255);

		if (State == TITLE)
		{
			init();
		}
		else if (State == EXP)
		{
			exp();
		}
		else if (State == PLAY)
		{
			update();
		}
		else if (State == RESULT)
		{
			result();
		}
		if (isTrigger(KEY_ENTER)) 
		{
			main()->backToMenu();
		}
	}
}
