#include "../../libOne/inc/libOne.h"
#include "../MAIN/MAIN.h"
#include "GAME08.h"
#include "SCENEMANAGER.h"
#include "TITLESCENE.h"
#include "DIFFICULTYSCENE.h"
#include "GAMESCENE.h"
#include "RESULTSCENE.h"

namespace GAME08
{
	SCENEMANAGER sceneMgr;

	int GAME::create()
	{
		//loadPackage("assets.package");
		//disableEscapeKey();
		hideCursor();
		sceneMgr.change(SCENEMANAGER::TITLE);
		return 0;
	}

	void GAME::destroy()
	{
		sceneMgr.shutdown();
		//deletePackage();
		showCursor();
	}

	void GAME::proc()
	{
		if (isTrigger(KEY_M))main()->backToMenu();//Mキーでメニューに戻る
		if (isTrigger(KEY_Q))closeWindow();//Qキーでプログラム終了
		sceneMgr.update();
	}
}
