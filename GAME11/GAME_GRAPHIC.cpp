#include "../../libOne/inc/libOne.h"
#include "GAME11.h"
#include"GAME_GRAPHIC.h"
#include"PLAYER_and_NPC.h"
namespace GAME11 {

	void MAP::MOVE_CAMERA(PLAYER* player) {
		int cameraX = (int)(player->X - width / 2);
		int cameraY = (int)(player->Y - height / 2);

		for (int y = -1; y <= height / TILE_SIZE + 1; y++) {
			for (int x = -1; x <= width / TILE_SIZE + 1; x++) {
				// ワールド座標のタイル位置
				int worldX = (cameraX / TILE_SIZE + x) * TILE_SIZE;
				int worldY = (cameraY / TILE_SIZE + y) * TILE_SIZE;

				int drawX = worldX - cameraX;
				int drawY = worldY - cameraY;

				// 床タイルを描画
				fill(255);
				rect((float)drawX, (float)drawY, (float)(TILE_SIZE - 1), (float)(TILE_SIZE - 1));
				//if (rand() % 1000 == 0) {
				Like_a_BUG(100, 255, 1);
				rect(((drawX)+BUG_X), ((drawY)+BUG_Y), (float)(TILE_SIZE - 1), (float)(TILE_SIZE - 1));
				//}

			}
		}
		/*
		// プレイヤーは常に画面中央
		int playerDrawX = width / 2 - player->Width / 2;
		int playerDrawY = height / 2 - player->Height / 2;
		fill(255, 0, 0);
		rect(playerDrawX, playerDrawY, player->Width, player->Height);
		*/
	}
	void MAP::RANDOM_SET() {
		srand((unsigned int)time(0));
	}
	void MAP::Like_a_BUG(int percent, int color, int pattern) {
		int BUG_Flag = 0;
		BUG_X = 0; BUG_Y = 0;
		if (rand() % percent == 0) {
			if (rand() % (percent / 2) == 0) {
				fill(255, 0, 0); BUG_Flag = 1;
			}
			else if (rand() % (percent / 2) == 1) {
				fill(0, 255, 0); BUG_Flag = 1;
			}
			else if (rand() % (percent / 2) == 2) {
				fill(0, 0, 255); BUG_Flag = 1;
			}
			else { fill((float)color); }
		}
		else {
			fill((float)color);
		} if (pattern == 1 && BUG_Flag == 1) {
			if (rand() % 3 == 0) {
				BUG_X += 5;
			} if (rand() % 3 == 1) {
				BUG_X -= 5;
			} if (rand() % 3 == 2) {
				BUG_Y += 5;
			} if (rand() % 3 == 3) {
				BUG_Y -= 5;
			}
		}
	}
	void MAP::DRAW_BUG() {
		Like_a_BUG(30, 0, 1);
		if (rand() % 100 == 0) {
			rect(((rand() % Yoko) + BUG_X) + 10, ((rand() % Tate) + BUG_Y) + 10, (float)TILE_SIZE, (float)TILE_SIZE);
		}
	}
	int MAP::DRAW_TEXT() {
		textMode(BOTTOM);
		textSize(80);
		text("O : OPTION", 0, Tate);
		text("M : EXIT", Yoko - 360, Tate);
		if (isTrigger(KEY_M)) {
			return 1;
		}
		else if (isTrigger(KEY_O)) {
			return 2;
		}
		else {
			return 0;
		}
	}
}