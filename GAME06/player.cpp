#include "../../libOne/inc/graphic.h"
#include "../../libOne/inc/input.h"
#include"player.h"
#include "item.h"
#include "../../libOne/inc/sound.h"
namespace GAME06
{
	void PLAYER::create()
	{
		//PLAYERクラスの画像と音楽のロード
		Img = loadImage("../../MiniGamesV3_DC2/MAIN/assets/game06/\\player.png");
		Sound = loadSound("../../MiniGamesV3_DC2/MAIN/assets/game06/\\itemget.wav");
		Sound2 = loadSound("../../MiniGamesV3_DC2/MAIN/assets/game06/\\itemget2.wav");
	}
	void PLAYER::init()
	{
		//PLAYERクラス変数の初期化
		Timer =5400;
		Score = 0;
		Px = Width / 2;
		Py = 960;
		Pvx = 20;
		Pvy = 5;
		Get = 0;
	}
	void PLAYER::update()
	{
		//プレイヤーをキーを使って左右に動かす
		if (isPress(KEY_A))Px -= Pvx;
		if (isPress(KEY_D))Px += Pvx;
		if (Px > 2000)
		{
			Px = -100;
		}
		if (Px < -100)
		{
			Px = 2000;
		}
	}
	void PLAYER::draw()
	{
		//画像の描画
		image(Img, Px, Py, 0, 0.3f);
	}
	void PLAYER::score()
	{
		//スコアと残り時間の表示
		textSize(150);
		text((let)"SCORE:" + Score, width / 4 +220, height / 2);
		text((let)"残り時間:" + Timer, width / 4, height / 2 + 200);
	}
	bool PLAYER::hit(ITEM& item)
	{
		if (item.I == 0)
		{
			//当たり判定とその時の処理
			if (left() > item.right() ||
				right() < item.left() ||
				top() > item.bottom() ||
				bottom() < item.top())
			{
				return false;
			}
			playSound(Sound);
			Score++;
			//Timer += 120;
			item.init();
			return true;
		}
		else if (item.I == 1)
		{
			if (left() > item.right() ||
				right() < item.left() ||
				top() > item.bottom() ||
				bottom() < item.top())
			{
				return false;
			}
			playSound(Sound2);
			//Timer -= 120;
			Get += 1;
			item.init();
			return true;
		}
	}
}