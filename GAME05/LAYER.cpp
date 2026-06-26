#include"../../libOne/inc/window.h"
#include"../../libOne/inc/graphic.h"
#include"GAME.h"
#include"GAME05.h"
#include"CONTAINER.h"
#include "MAP.h"
#include "LAYER.h"
#include"CHARACTER_MANAGER.h"
namespace GAME05 {
	LAYER::LAYER(class GAME_* game) :
		GAME_OBJECT(game) {}
	LAYER::~LAYER() {
		if (Layer.data) { delete[] Layer.data; Layer.data = 0; }
	}
	void LAYER::create() {
		Layer = game()->container()->data().layer;
	}
	void LAYER::init() {
		//ファイルを開く
		FILE* fp;
		fopen_s(&fp, Layer.fileName, "rb");
		WARNING(fp == 0, "レイヤーデータを読み込めません", Layer.fileName);
		//ファイルサイズ取得
		fseek(fp, 0, SEEK_END);
		int fileSize = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		//リトライ時、Dataは0でないので開放。
		if (Layer.data) { delete[] Layer.data; Layer.data = 0; }
		//サイズ分のdata配列を用意する
		Layer.data = new char[fileSize];
		//データを読み込む
		fread(Layer.data, sizeof(char), fileSize, fp);
		fclose(fp);
		//行数、列数を数える（最後の行も必ず改行して終わっていることが条件）
		Layer.rows = 0;
		Layer.cols = 0;//改行２文字分を含んだ列数になる
		int cnt = 0;
		for (int i = 0; i < fileSize; i++) {
			cnt++;
			//行の最後の文字
			if (Layer.data[i] == '\n') {
				if (Layer.rows == 0) {
					//最初の行の列数
					Layer.cols = cnt;
				}
				else if (Layer.cols != cnt) {
					//行ごとの列数が違ったらエラー
					WARNING(1, "列数が不揃い", "");
				}
				//行を数えてカウンタをリセット
				Layer.rows++;
				cnt = 0;
			}
		}
		if (fileSize % Layer.cols != 0) {
			WARNING(1, "最後の行を改行していない", "");
		}
		Layer.dispCols = (int)width / Layer.chipSize + 2;//表示すべき列数
		Layer.worldWidth = (float)Layer.chipSize * (Layer.cols - 2);//ワールドの横幅
		Layer.endWorldX = Layer.worldWidth - width;//表示できる最後の座標
		Layer.wx = 0.0f;//現在表示しているワールド座標
	}
	void LAYER::update() {
		//プレイヤーが画面の中央を超えた分だけスクロール
		Layer.wx = game()->map()->wx();
		if (Layer.wx > Layer.endWorldX) {
			Layer.wx = Layer.endWorldX;
		}
	}
	void LAYER::draw() {
		int startCol = (int)Layer.wx / Layer.chipSize;//表示開始列
		int endCol = startCol + Layer.dispCols;//表示終了列
		for (int c = startCol; c < endCol; c++) {
			float wx = (float)Layer.chipSize * c;
			for (int r = 0; r < Layer.rows; r++) {
				float wy = (float)Layer.chipSize * r;
				char charaId = Layer.data[r * Layer.cols + c];
				if (charaId >= '0' && charaId <= '9') {
					float px = wx - Layer.wx;
					float py = wy - Layer.wy;
					if (charaId == '1')image(Layer.blockImg, px, py);
					else if (charaId == '2')image(Layer.block2Img, px, py);
					else if (charaId == '3')image(Layer.block3Img, px, py);
					else if (charaId == '4')image(Layer.block4Img, px, py);
					else if (charaId == '5')image(Layer.block5Img, px, py);
					else if (charaId == '6')image(Layer.block6Img, px, py);
					else if (charaId == '7')image(Layer.block7Img, px, py);
					else if (charaId == '8')image(Layer.block8Img, px, py);
					else if (charaId == '9')image(Layer.block9Img, px, py);
				}
				else if (charaId >= 'a' && charaId <= 'z') {
					game()->characterManager()->appear(charaId, wx, wy);
					Layer.data[r * Layer.cols + c] = '.';
				}
			}
		}
	}

	//ウィンドウからのはみだし判定用---------------------------------------------------------
	float LAYER::wDispLeft() {//表示領域の左端を取得
		return Layer.wx - Layer.chipSize;
	}
	float LAYER::wDispRight() {//表示領域の右端を取得
		return Layer.wx + width;
	}
}