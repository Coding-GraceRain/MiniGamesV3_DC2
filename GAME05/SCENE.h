#pragma once
#include "GAME_OBJECT.h"
namespace GAME05 {
	class SCENE :
		public GAME_OBJECT
	{
	public:
		SCENE(class GAME_* game) : GAME_OBJECT(game) {}
		virtual void create();//シーンの初期設定を行う関数
		virtual void init();//シーンの初期化を行う関数   
		virtual void proc();//シーンの処理を行う関数
		virtual void update();//シーンの更新を行う関数
		virtual void draw();//シーンの描画を行う関数
		virtual void nextScene();//次のシーンに切り替える関数
	};
}
