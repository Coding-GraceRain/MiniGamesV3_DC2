#pragma once
namespace GAME05 {
	class GAME_OBJECT
	{
	private:
		class GAME_* Game = nullptr;//ゲームクラスのポインタ
	public:
		GAME_OBJECT(class GAME_* game);//コンストラクタ
		virtual ~GAME_OBJECT();//デストラクタ
		class GAME_* game() { return Game; }//ゲームクラスのポインタを返す関数
	};
}