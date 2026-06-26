#pragma once
#include "GAME_OBJECT.h"
namespace GAME05 {
	class LAYER :
		public GAME_OBJECT
	{
	public:
		struct DATA {
			const char* fileName = 0;
			int blockImg = 0;//マップチップの画像1
			int block2Img = 0;//マップチップの画像2
			int block3Img = 0;//マップチップの画像3
			int block4Img = 0;//マップチップの画像4
			int block5Img = 0;//マップチップの画像5
			int block6Img = 0;//マップチップの画像6
			int block7Img = 0;//マップチップの画像7
			int block8Img = 0;//マップチップの画像8
			int block9Img = 0;//マップチップの画像9

			int chipSize = 0;
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
			float centerX = 0;//ワールド座標の中心。ウィンドウの幅の半分からマップチップの幅の半分を引いて計算する。
		};
		enum CHARA_ID {
			PLAYER_ID = 'a',//マップデータ上でのプレイヤーの識別子
		};
	private:
		DATA Layer;
	public:
		LAYER(class GAME_* game);
		~LAYER();
		void create();
		void init();
		void update();
		void draw();
		float wx() { return Layer.wx; }//world position xを返す関数
		float wy() { return Layer.wy; }//world position yを返す関数
		int chipSize() { return Layer.chipSize; }//マップチップの一辺のドット数

		//ウィンドウ枠からのはみだし判定用---------------------------------------------------
		float wDispLeft();//ウィンドウの左端に対応するワールド座標を返す関数
		float wDispRight();//ウィンドウの右端に対応するワールド座標を返す関数
	};
}