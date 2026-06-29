#include "../../libOne/inc/libOne.h"
#include "../../libOne/inc/input.h"
#include"GAME08.h"
#include "PLAYER.h"
namespace GAME08
{
	PLAYER::PLAYER(GAME* game)
		:ACTOR(game)
	{
	}
	PLAYER::~PLAYER()
	{
	}
	void PLAYER::init()
	{
		setW(150);
		setH(15);
		setPx(game()->court()->w() / 2 - w() / 2);
		setPy(game()->court()->h() - 200);
		setSp(5);
	}
	void PLAYER::update()
	{
		if (isPress(KEY_D))setPx(px() + sp());
		if (isPress(KEY_A))setPx(px() - sp());
		float lim = 5;
		if (px() < lim)setPx(lim);
		float courtW = game()->court()->w();
		if (px() > courtW - w() - lim){
			setPx(courtW - w() - lim);
		}
	}
	void PLAYER::draw()
	{
		stroke(255);
		strokeWeight(h());
		float px = game()->court()->px() + this->px();
		line(px, py(), px + w(), py());
	}
}