#include "../../libOne/inc/libOne.h"
#include"item.h"
#include <cstdlib>
namespace GAME06
{
	void ITEM::create()
	{
		//ITEMクラスの画像のロード
		Img = loadImage("../../MiniGamesV3_DC2/MAIN/assets/game06/\\item.png");
		Img2 = loadImage("../../MiniGamesV3_DC2/MAIN/assets/game06/\\item2.png");
	}
	void ITEM::init()
	{
		//ITEMクラス変数の初期化
		I = rand() % 2;
		Ix = rand() % 1800;
		Iy = 0.0f;
		Ivx = 5.0f;
		Ivy = 10.0f;
	}
	void ITEM::update()
	{
		//画像を上から下に動かす
		Iy += Ivy;
		if (Iy > height)
		{
			init();
		}
	}
	void ITEM::draw()
	{
		//画像の描画
		I %= 2;
		if (I == 0)
		{
			image(Img, Ix, Iy, 0, 0.3f);
		}
		else
		{
			image(Img2, Ix, Iy, 0, 0.3f);
		}
	}
}