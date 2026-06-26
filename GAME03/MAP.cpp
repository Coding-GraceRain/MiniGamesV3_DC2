#include "MAP.h"
#include "../../libOne/inc/libOne.h"
#include "CONTAINER.h"
#include "GAME03.h"
#include "CHARACTER_MANAGER.h"
namespace GAME03
{
	MAP::MAP(class GAME* game) :
		GAME_OBJECT(game) {
	}
	MAP::~MAP() {
		if (Map.map) { delete[] Map.map; Map.map = 0; }
	}
	void MAP::create() {
		Map = game()->container()->data().map;
	}
	void MAP::init(const char* fileName) {

		Map.gimmickButton = game()->container()->data().map.gimmickButton;

		FILE* fp;

		fopen_s(&fp, fileName, "rb");
		WARNING(fp == 0, "マップデータを読み込めません", fileName);
		fseek(fp, 0, SEEK_END);
		int fileSize = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		if (Map.map) { delete[] Map.map; Map.map = 0; }
		Map.map = new char[fileSize];
		fread(Map.map, sizeof(char), fileSize, fp);

		fclose(fp);

		Map.cols = 0;
		Map.rows = 0;
		int cnt = 0;


		for (int i = 0; i < fileSize; i++) {
			cnt++;
			if (Map.map[i] == '\n') {
				if (Map.rows == 0) {
					Map.cols = cnt;
				}
				else if (Map.cols != cnt) {
					WARNING(1, "列数が不揃い", "");
				}
				Map.rows++;
				cnt = 0;
			}
		}
		if (fileSize % Map.cols != 0) {
			WARNING(1, "最後の行を改行していない", "");
		}
	}
	void MAP::draw() {
		rectMode(CORNER);
		for (int c = 0; c < Map.cols; c++) {
			Map.px = (float)Map.chipSize * c;
			for (int r = 0; r < Map.rows; r++) {
				Map.py = (float)Map.chipSize * r;
				int idx = r * Map.cols + c;
				char charaId = Map.map[idx];
				if (charaId == '1') {
					image(Map.blockImg, Map.px, Map.py);
				}
				if (charaId == '2' && Map.gimmickButton == 0) {
					image(Map.barrierImg, Map.px, Map.py);
				}
				if (charaId == '2' && Map.gimmickButton == 1) {
					Map.map[idx] = '.';
				}
				else if (charaId >= 'a' && charaId <= 'z') {
					game()->characterManager()->appear(charaId, Map.px, Map.py);
					Map.map[idx] = '.';
				}
			}
		}
	}
	bool MAP::collisionCheck(float wx, float wy) {
		int col = (int)wx / Map.chipSize;
		int row = (int)wy / Map.chipSize;

		if ((col < 0) || (col > Map.cols) || (row < 0) || (row > Map.rows)) {
			return false;
		}
		if (Map.map[col + row * Map.cols] == '1' ||
			Map.map[col + row * Map.cols] == '2') {
			return true;
		}
		return false;
	}
	bool MAP::collisionCharaLeft(float wx, float wy) {
		bool leftTop = collisionCheck(wx, wy);
		bool leftBottom = collisionCheck(wx, wy + Map.chipSize - 1);
		return leftTop || leftBottom;
	}
	bool MAP::collisionCharaRight(float wx, float wy) {
		bool rightTop = collisionCheck(wx + Map.chipSize - 1, wy);
		bool rightBottom = collisionCheck(wx + Map.chipSize - 1, wy + Map.chipSize - 1);
		return rightTop || rightBottom;
	}
	bool MAP::collisionCharaTop(float wx, float wy) {
		bool topLeft = collisionCheck(wx, wy);
		bool topRight = collisionCheck(wx + Map.chipSize - 1, wy);
		return topLeft || topRight;
	}
	bool MAP::collisionCharaBottom(float wx, float wy) {
		bool bottomLeft = collisionCheck(wx, wy + Map.chipSize);
		bool bottomRight = collisionCheck(wx + Map.chipSize - 1, wy + Map.chipSize);
		return bottomLeft || bottomRight;
	}
	bool MAP::collisionCharaRect(float wLeft, float wTop, float wRight, float wBottom) {
		bool rightTop = collisionCheck(wRight, wTop);
		bool rightBottom = collisionCheck(wRight, wBottom);
		bool leftTop = collisionCheck(wLeft, wTop);
		bool leftBottom = collisionCheck(wLeft, wBottom);
		return rightTop || rightBottom || leftTop || leftBottom;
	}
	void MAP::gimmick() {
		Map.gimmickButton = 1;
	}
}