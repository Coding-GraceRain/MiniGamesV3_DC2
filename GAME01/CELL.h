//CELLを定義
//０～４の数字で床、壁、自機、敵の管理
#pragma once
namespace GAME01
{
	class CELL {
	public:
		int type;//0=床 1=壁 2=自機 3=敵 4=階段 5=回復 6=実数値強化 7=ボス 8=宝箱 
		int enemyType;
		int Px, Py;
	};
}