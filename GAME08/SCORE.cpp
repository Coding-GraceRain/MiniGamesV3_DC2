#include "../../libOne/inc/libOne.h"
#include "../../libOne/inc/input.h"
#include"GAME08.h"
#include "SCORE.h"
namespace GAME08
{
	SCORE::SCORE(GAME* game)
		:ACTOR(game)
	{
		
	}
	SCORE::~SCORE()
	{
	}
	void SCORE::init()
	{
		PlayerScore = 0;
		Player2Score = 0;
		ScoreFlag = false;
		WinerScore = 1;
	}
	void SCORE::update()
	{
		float courtH = game()->court()->h();
		float ballPy = game()->ball()->py();
		if (ballPy > 0 && ballPy < courtH) {
			ScoreFlag = false;
		}
		if (ScoreFlag == false) {
			if (ballPy < 0) {
				PlayerScore++;
				ScoreFlag = true;
			}
			else if (ballPy > courtH) {
				Player2Score++;
				ScoreFlag = true;
			}
		}
		if (PlayerScore >= 3 || Player2Score >= 3)
		{
			game()->GameOver();
		}
	}
	void SCORE::draw()
	{
		fill(255);
		float px = game()->court()->px() - 100;
		float py = game()->court()->h();
		textSize(100);
		textMode(BCENTER);
		text(Player2Score,px, 270);
		text(PlayerScore, px, py - 270);
	}
}