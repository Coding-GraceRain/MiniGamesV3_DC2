#pragma once
#include "SCENE.h"
namespace GAME05 {
	class STAGE :
		public SCENE
	{
	public:
		struct DATA {
			int backImg = 0;//背景の画像
			int gameClearImg = 0;//ゲームクリアの画像
			int gameOverImg = 0;//ゲームオーバーの画像
			float backToTitleTime = 0;//ゲームオーバーやゲームクリアからタイトルに戻るまでの時間。単位は秒。
			COLOR backColor;//背景の色
			COLOR gameOverColor;//ゲームオーバーの色
			COLOR gameClearColor;//ゲームクリアの色
			float logoPx = 0;//ロゴのX座標
			float logoPy = 0;//ロゴのY座標
		};
	private:
		DATA Stage;//ステージのデータ
		void BackGround();//背景の描画を行う関数
		void Logo(int img, const COLOR& color);//ゲームオーバーとゲームクリアのロゴの描画を行う関数
	public:
		STAGE(class GAME_* game) : SCENE(game) {}//コンストラクタ
		void create();//ステージの初期設定を行う関数
		void init();//ステージの初期化を行う関数
		void update();//ステージの更新を行う関数
		void draw();//ステージの描画を行う関数
		void nextScene();//次のシーンに切り替える関数
	};
}