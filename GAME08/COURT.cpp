#include "../../libOne/inc/libOne.h"
#include "COURT.h"
namespace GAME08
{
	COURT::COURT(GAME* game)
		:ACTOR(game)
	{
	}
	COURT::~COURT()
	{
	}
	void COURT::init()
	{
		setW(810);
		setH(1080); 
		setPx((1920-w())/2);
	}
	void COURT::update()
	{
	}
	void COURT::draw()
	{
		fill(0, 60, 60);
		stroke(255);
		strokeWeight(5);
		rect(px(), py(), w(), h());
	}
}