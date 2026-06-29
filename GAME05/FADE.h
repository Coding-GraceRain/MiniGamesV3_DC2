#pragma once
#include"GAME_OBJECT.h"
#include"../../libOne/inc/COLOR.h"
namespace GAME05 {
	class FADE :
		public GAME_OBJECT {
	public:
		struct DATA {
			COLOR color;//フェードの色
			float speed = 0;//フェードの速さ。単位はアルファ値の変化量/秒。
		};
	private:
		DATA Fade;//フェードのデータ
		enum class STATE {
			IN_TRIGGER, IN_NOW, IN_END,//IN_～はフェードインの状態。～_TRIGGERはトリガーが引かれた状態、～_NOWはフェード中の状態、～_ENDはフェードが終了した状態。
			OUT_TRIGGER, OUT_NOW, OUT_END//OUT_～はフェードアウトの状態。～_TRIGGERはトリガーが引かれた状態、～_NOWはフェード中の状態、～_ENDはフェードが終了した状態。
		};
		STATE State = STATE::OUT_END;//最初はフェードアウトが終了している状態
	public:
		FADE(class GAME_* game) : GAME_OBJECT(game) {}//コンストラクタ
		void create();//フェードの初期設定を行う関数
		void inTrigger();//フェードインのトリガーを引く関数
		void outTrigger();//フェードアウトのトリガーを引く関数
		void draw();//フェードの描画を行う関数
		int outEndFlag();//フェードアウトが終了したかどうかを返す関数
		int inEndFlag();//フェードインが終了したかどうかを返す関数
		void setSpeed(float speed);//フェードの速さをセットする関数
		void setColor(const COLOR& color);//フェードの色をセットする関数
	};
}