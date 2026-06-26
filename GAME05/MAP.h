#pragma once
#include"GAME_OBJECT.h"
namespace GAME05 {
	class MAP :
		public GAME_OBJECT
	{
	public:
		struct DATA {
			const char* fileName = 0;//マップデータのファイル名
			int blockImg = 0;//マップチップの画像
			int block2Img = 0;//マップチップの画像2
			int block3Img = 0;//マップチップの画像3
			int block4Img = 0;//マップチップの画像4
			int block5Img = 0;//マップチップの画像5
			int block6Img = 0;//マップチップの画像6
			int block7Img = 0;//マップチップの画像7
			int block8Img = 0;//マップチップの画像8
			int block9Img = 0;
			int goalImg = 0;//ゴールの画像
			int chipSize = 0; //正方形マップチップ画像の一辺のドット数
			char* data = 0; //データ配列のポインタ
			int cols = 0; //データの列数
			int rows = 0; //データの行数
			int dispCols = 0;//表示すべき列数。ワールド座標wxから、dispCols分のマップチップを描画する。
			int dispRows = 0;//表示すべき行数。ワールド座標wyから、dispRows分のマップチップを描画する。
			float wx = 0;//world position x
			float wy = 0;//world position y
			float worldWidth = 0;//ワールドの横幅。マップチップの列数から計算する。
			float worldHeight = 0;//ワールドの縦幅。マップチップの行数から計算する。
			float endWorldX = 0;//表示できる最後のワールド座標。ワールドの横幅からウィンドウの幅を引いて計算する。
			float endWorldY = 0;//表示できる最後のワールド座標。ワールドの縦幅からウィンドウの幅を引いて計算する。
			float centerX = 0;//ワールド座標の中心。ワールドの横幅からウィンドウの幅を引いて2で割って計算する。
		};
		enum CHARA_ID {
			PLAYER_ID = 'a',//マップデータ上でのプレイヤーの識別子
			PLAYER_BULLET_ID = 'b',
			SURAIMU_ID = 'c',//マップデータ上でのスライムの識別子
			TREE_ID = 'd',
			TREE_BULLET_ID = 'e',
			BOSS_ID = 'f',
			BOSS_BULLET_ID = 'g',
		};
	private:
		DATA Map;//マップのデータ
	public:
		MAP(class GAME_* game);
		~MAP();
		void create();//マップデータの読み込み
		void init();//マップの初期設定を行う関数
		void update();//マップの更新を行う関数
		void draw();//マップの描画を行う関数
		float wx() { return Map.wx; }//world position xを返す関数
		float wy() { return Map.wy; }//world position yを返す関数
		int chipSize() { return Map.chipSize; }//マップチップの一辺のドット数
		//マップチップとキャラの当たり判定に使用する関数群---------------------------------------
		bool collisionCheck(float wx, float wy);//下の当たり判定関数群から呼び出して使う関数
		bool collisionCharaLeft(float wx, float wy);//マップチップとキャラの左辺が重なっているかチェックする関数
		bool collisionCharaRight(float wx, float wy);//マップチップとキャラの右辺が重なっているかチェックする関数
		bool collisionCharaTop(float wx, float wy);//マップチップとキャラの上辺が重なっているかチェックする関数
		bool collisionCharaBottom(float wx, float wy);//マップチップとキャラの下辺が重なっている、または、接しているかチェックする関数
		bool collisionCharaRect(float wLeft, float wTop, float wRight, float wBottom);//弾用
		//ウィンドウ枠からのはみだし判定用---------------------------------------------------
		float wDispLeft();//ウィンドウの左端に対応するワールド座標を返す関数
		float wDispRight();//ウィンドウの右端に対応するワールド座標を返す関数
	};
}
