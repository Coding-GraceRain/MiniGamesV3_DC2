#include "../../libOne/inc/libOne.h"
#include "../MAIN/MAIN.h"
#include "GAME07.h"


namespace GAME07
{

	int GAME::create()
	{
		taitle.create();
		return 0;
	}

	void GAME::destroy()
	{

	}

	void GAME::proc()
	{
			if (isTrigger(KEY_ENTER)) {
				main()->backToMenu();
			}
			taitle.state();
			
			
	}

}
