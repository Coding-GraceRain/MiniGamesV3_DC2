#include"../../libOne/inc/window.h"
#include"../../libOne/inc/graphic.h"
#include"GAME.h"
#include"GAME05.h"
#include"CONTAINER.h"
#include "MAP.h"
#include "LAYER2.h"
#include"CHARACTER_MANAGER.h"
namespace GAME05 {
	LAYER2::LAYER2(class GAME_* game) :
		GAME_OBJECT(game) {}
	LAYER2::~LAYER2() {
		if (Layer2.data) { delete[] Layer2.data; Layer2.data = 0; }
	}
	void LAYER2::create() {
		Layer2 = game()->container()->data().layer2;
	}
	void LAYER2::init() {
		//ファイルを開く
		FILE* fp;
		fopen_s(&fp, Layer2.fileName, "rb");
		WARNING(fp == 0, "レイヤーデータを読み込めません", Layer2.fileName);
		//ファイルサイズ取得
		fseek(fp, 0, SEEK_END);
		int fileSize = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		//リトライ時、Dataは0でないので開放。
		if (Layer2.data) { delete[] Layer2.data; Layer2.data = 0; }
		//サイズ分のdata配列を用意する
		Layer2.data = new char[fileSize];
		//データを読み込む
		fread(Layer2.data, sizeof(char), fileSize, fp);
		fclose(fp);
		//行数、列数を数える（最後の行も必ず改行して終わっていることが条件）
		Layer2.rows = 0;
		Layer2.cols = 0;//改行２文字分を含んだ列数になる
		int cnt = 0;
		for (int i = 0; i < fileSize; i++) {
			cnt++;
			//行の最後の文字
			if (Layer2.data[i] == '\n') {
				if (Layer2.rows == 0) {
					//最初の行の列数
					Layer2.cols = cnt;
				}
				else if (Layer2.cols != cnt) {
					//行ごとの列数が違ったらエラー
					WARNING(1, "列数が不揃い", "");
				}
				//行を数えてカウンタをリセット
				Layer2.rows++;
				cnt = 0;
			}
		}
		if (fileSize % Layer2.cols != 0) {
			WARNING(1, "最後の行を改行していない", "");
		}
		Layer2.dispCols = (int)width / Layer2.chipSize + 2;//表示すべき列数
		Layer2.worldWidth = (float)Layer2.chipSize * (Layer2.cols - 2);//ワールドの横幅
		Layer2.endWorldX = Layer2.worldWidth - width;//表示できる最後の座標
		Layer2.wx = 0.0f;//現在表示しているワールド座標
	}
	void LAYER2::update() {
		//プレイヤーが画面の中央を超えた分だけスクロール
		Layer2.wx = game()->map()->wx();
		if (Layer2.wx > Layer2.endWorldX) {
			Layer2.wx = Layer2.endWorldX;
		}
	}
	void LAYER2::draw() {
		int startCol = (int)Layer2.wx / Layer2.chipSize-2;//表示開始列
		int endCol = startCol + Layer2.dispCols+2;//表示終了列
		for (int c = startCol; c < endCol; c++) {
			float wx = (float)Layer2.chipSize * c;
			for (int r = 0; r < Layer2.rows; r++) {
				float wy = (float)Layer2.chipSize * r;
				char charaId = Layer2.data[r * Layer2.cols + c];
				if (charaId >= '0' && charaId <= '9') {
					float px = wx - Layer2.wx;
					float py = wy - Layer2.wy;
					if (charaId == '1')image(Layer2.blockImg, px, py);
					else if (charaId == '2')image(Layer2.block2Img, px, py);
					else if (charaId == '3')image(Layer2.block3Img, px, py);
					else if (charaId == '4')image(Layer2.block4Img, px, py);
					else if (charaId == '5')image(Layer2.block5Img, px, py);
					else if (charaId == '6')image(Layer2.block6Img, px, py);
					else if (charaId == '7')image(Layer2.block7Img, px, py);
					else if (charaId == '8')image(Layer2.block8Img, px, py);
					else if (charaId == '9')image(Layer2.block9Img, px, py);
				}
				else if (charaId >= 'a' && charaId <= 'z') {
					game()->characterManager()->appear(charaId, wx, wy);
					Layer2.data[r * Layer2.cols + c] = '.';
				}
			}
		}
	}

	//ウィンドウからのはみだし判定用---------------------------------------------------------
	float LAYER2::wDispLeft() {//表示領域の左端を取得
		return Layer2.wx - Layer2.chipSize;
	}
	float LAYER2::wDispRight() {//表示領域の右端を取得
		return Layer2.wx + width;
	}
}