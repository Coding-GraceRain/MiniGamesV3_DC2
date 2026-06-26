
#include "../../libOne/inc/libOne.h"
#include"back.h"
namespace GAME06
{
	void BACK::create()
	{
		//背景画像のロード
		Img = loadImage("../../MiniGamesV3_DC2/MAIN/assets/game06/\\back2.jpg");
	}
	void BACK::draw()
	{
		//背景を描画
		image(Img, 0, 0);
	}
}