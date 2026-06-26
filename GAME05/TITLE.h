#pragma once
#include"SCENE.h"
#include"../../libOne/inc/COLOR.h"
namespace GAME05 {
	class TITLE :
		public SCENE
	{
	public:
		struct DATA {
			int backImg = 0;//背景の画像
		};
	public:
		TITLE(class GAME_* game) : SCENE(game) {}
		void init();//シーンの初期化を行う関数
		void draw();//シーンの描画を行う関数
		void nextScene();//次のシーンに切り替える関数
	};
}