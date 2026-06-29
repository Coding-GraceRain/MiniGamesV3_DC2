#include "ACTOR.h"
namespace GAME08
{
	ACTOR::ACTOR(GAME* game)
		:Game(game)
	{
	}
	ACTOR::~ACTOR()
	{
		Game = 0;
	}
}