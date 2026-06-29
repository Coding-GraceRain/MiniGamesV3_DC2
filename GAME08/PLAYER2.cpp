#include "PLAYER2.h"
#include "../../libOne/inc/libOne.h"
#include "../../libOne/inc/input.h"
#include"GAME08.h"

namespace GAME08
{
	PLAYER2::PLAYER2(GAME* game)
		:ACTOR(game)
	{
	}
	PLAYER2::~PLAYER2()
	{
	}
	void PLAYER2::init()
	{
		setW(150);
		setH(15);
		setPx(game()->court()->w() / 2 - w() / 2);
		setPy(200);
		setSp(5);
	}
	void PLAYER2::update()
	{
		if (isPress(KEY_L))setPx(px() + sp());
		if (isPress(KEY_J))setPx(px() - sp());
		float lim = 5;
		if (px() < lim)setPx(lim);
		float courtW = game()->court()->w();
		if (px() > courtW - w() - lim) {
			setPx(courtW - w() - lim);
		}
	}
	void PLAYER2::draw()
	{
		stroke(255);
		strokeWeight(h());
		float px = game()->court()->px() + this->px();
		line(px, py(), px + w(), py());
	}
}