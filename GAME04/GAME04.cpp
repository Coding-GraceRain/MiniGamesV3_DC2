#include "../../libOne/inc/libOne.h"
#include "../MAIN/MAIN.h"
#include <math.h>
#include "GAME04.h"
#include <sstream> 
#include <cstdlib>  // rand() を使うために必要
#include <ctime>    // srand() と時間取得用
namespace GAME04
{
	int playerShootTimer = 0;   // プレイヤー弾の発射クールダウン用タイマー
	const int playerShootInterval = 25;  // 発射間隔（フレーム数、ここは調整可能）
	int endStateTimer = 0;       // ゲーム終了状態表示用のタイマー
	const int endStateDuration = 180;  // 表示時間（フレーム数、60fpsなら3秒）
	enum GameState {
		TITLE,
		PLAY,
		GAME_OVER,
		GAME_CLEAR
	};
	GameState state = TITLE;
	float distance(float x1, float y1, float x2, float y2) {
		return sqrtf((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
	}
	int GAME::create()
	{

		player = new PLAYER;
		enemy = new ENEMY;
		player->hp = 10;
		enemy->hp = 20;
		for (int i = 0; i < MAX_BULLET; i++) {
			bullets[i].hp = 0;
			ebullets[i].hp = 0;
		}

		enemyShootTimer = 0;
		return 0;
	}
	void GAME::destroy()
	{

		delete player; player = nullptr;
		delete enemy; enemy = nullptr;

	}

	void GAME::move() {
		playerShootTimer++;

		player->move();
		enemy->move();

		for (int i = 0; i < MAX_BULLET; i++) {
			bullets[i].move();
			ebullets[i].move();
		}

		if (playerShootTimer > playerShootInterval && isTrigger(KEY_SPACE)) {
			for (int i = 0; i < MAX_BULLET; i++) {
				if (bullets[i].hp == 0) {
					bullets[i].shoot(player->px, player->py);
					playerShootTimer = 0;
					break;
				}
			}
		}

		srand((unsigned int)time(nullptr));

		enemyShootTimer++;
		if (enemyShootTimer > 60) {
			int bulletsFired = 0;
			for (int i = 0; i < MAX_BULLET; i++) {
				if (ebullets[i].hp == 0) {
					// vx は -30 〜 30 の間のランダムな値
					float vx = (rand() % 61) - 30;  // 0〜60 の整数を生成してから -30で範囲をずらす

					// vy は 5 〜 15 の間のランダムな値
					float vy = (rand() % 7) + 3;   // 0〜10 の整数を生成してから +5で範囲をずらす

					ebullets[i].shoot(enemy->px, enemy->py + enemy->ofsY, vx, vy);
					bulletsFired++;

					if (bulletsFired >= 11) break;
				}
			}
			enemyShootTimer = 0;
		}

		for (int i = 0; i < MAX_BULLET; i++) {
			if (bullets[i].hp > 0) {
				float d = distance(enemy->px, enemy->py, bullets[i].px, bullets[i].py);
				if (d < enemy->pr / 2 + bullets[i].pr / 2) {
					bullets[i].hp = 0;     // 弾は消える
					enemy->hp = (enemy->hp > 0) ? enemy->hp - 1 : 0;  // HP減少、0未満防止
					printf("Enemy hit! HP: %d\n", enemy->hp);
					if (enemy->hp <= 0) {
						print("Enemy defeated!\n");
					}
				}
			}
		}
		for (int i = 0; i < MAX_BULLET; i++) {
			if (ebullets[i].hp > 0) {
				float d = distance(player->px, player->py, ebullets[i].px, ebullets[i].py);
				if (d < player->pr / 2 + ebullets[i].pr / 2) {
					ebullets[i].hp = 0;    // 弾は消える
					player->hp = (player->hp > 0) ? player->hp - 1 : 0;  // HP減少、0未満防止
					printf("Player hit! HP: %d\n", player->hp);
					if (player->hp <= 0) {
						print("Player is dead!\n");
					}
				}
			}
		}
		if (player->hp <= 0) {
			if (state != GAME_OVER) {
				state = GAME_OVER;
				endStateTimer = 0;  // タイマーリセット
			}
		}
		if (enemy->hp <= 0) {
			if (state != GAME_CLEAR) {
				state = GAME_CLEAR;
				endStateTimer = 0;  // タイマーリセット
			}
		}



	}


	void GAME::draw() {
		player->draw();
		enemy->draw();

		for (int i = 0; i < MAX_BULLET; i++) {
			bullets[i].draw();
			ebullets[i].draw();
		}
	}

	void GAME::proc()
	{

		clear(0, 0, 64);

		if (state == TITLE) {
			// タイトル画面
			textSize(80);
			fill(255, 255, 0);
			text("SHOOTING GAME", 600,500);
			textSize(40);
			fill(255);
			text("SPACEキーでスタート", 600, 600);
			text("ENTERキー; メニューに戻る", 600, 700);
			if (isTrigger(KEY_SPACE)) {
				create();
				state = PLAY;
			}
		}
		else if (state == PLAY) {
			move();


			draw();
			textSize(50);
			fill(255, 255, 0);
			std::stringstream ss;
			ss << "Player HP: " << player->hp;
			text(ss.str().c_str(), 50, 50);
			ss.str("");  // 文字列をクリア
			ss << "Enemy HP: " << enemy->hp;
			text(ss.str().c_str(), 50, 120);
			if (player->hp <= 0) {
				text("GAME OVER", 600, 600);
			}
			if (enemy->hp <= 0) {
				text("YOU WIN!", 600, 600);
			}
			textSize(50);
			fill(255, 255, 0);
			
			fill(255);
			text("SPACEキー: 撃つ  Zキー: タイトルに戻る ENTERキー; メニューに戻る", 0, 1080);
		}
		if (isTrigger(KEY_ENTER)) {
			state = TITLE;
			destroy();
			main()->backToMenu();
		}
			if (isTrigger(KEY_Z)) {
				state = TITLE;
				destroy();
				
			}
			else if (state == GAME_OVER) {
				endStateTimer++;
				textSize(80);
				fill(255, 0, 0);
				text("GAME OVER", 500, 500);
				textSize(40);
				fill(255);
				text("Zキーでタイトルへ戻る　ENTERキー; メニューに戻る", 500, 700);

				if (isTrigger(KEY_Z)) {
					state = TITLE;
					destroy();
				}
			}
			else if (state == GAME_CLEAR) {
				endStateTimer++;
				textSize(80);
				fill(0, 255, 0);
				text("YOU WIN!", 500, 500);
				textSize(40);
				fill(255);
				text("Zキーでタイトルへ戻る　ENTERキー; メニューに戻る", 500, 700);

				if (endStateTimer > endStateDuration) {
					state = TITLE;
					destroy();
				}
				if (isTrigger(KEY_Z)) {
					state = TITLE;
					destroy();
				}
			}
		
	}
}
