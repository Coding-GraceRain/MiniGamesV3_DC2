#include "../../libOne/inc/libOne.h"
#include "../MAIN/MAIN.h"
#include <math.h>
#include "GAME04.h"
#include <sstream> 
#include <cstdlib>  // rand() ���g�����߂ɕK�v
#include <ctime>    // srand() �Ǝ��Ԏ擾�p
namespace GAME04
{
	int playerShootTimer = 0;   // �v���C���[�e�̔��˃N�[���_�E���p�^�C�}�[
	const int playerShootInterval = 25;  // ���ˊԊu�i�t���[�����A�����͒����\�j
	int endStateTimer = 0;       // �Q�[���I����ԕ\���p�̃^�C�}�[
	const int endStateDuration = 180;  // �\�����ԁi�t���[�����A60fps�Ȃ�3�b�j
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
					// vx �� -30 ? 30 �̊Ԃ̃����_���Ȓl
					float vx = (rand() % 21) - 10;  // 0?60 �̐����𐶐����Ă��� -30�Ŕ͈͂����炷

					// vy �� 5 ? 15 �̊Ԃ̃����_���Ȓl
					float vy = (rand() % 11) + 2;   // 0?10 �̐����𐶐����Ă��� +5�Ŕ͈͂����炷

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
					bullets[i].hp = 0;     // �e�͏�����
					enemy->hp = (enemy->hp > 0) ? enemy->hp - 1 : 0;  // HP�����A0�����h�~
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
					ebullets[i].hp = 0;    // �e�͏�����
					player->hp = (player->hp > 0) ? player->hp - 1 : 0;  // HP�����A0�����h�~
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
				endStateTimer = 0;  // �^�C�}�[���Z�b�g
			}
		}
		if (enemy->hp <= 0) {
			if (state != GAME_CLEAR) {
				state = GAME_CLEAR;
				endStateTimer = 0;  // �^�C�}�[���Z�b�g
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
		ShowCursor(FALSE);
		if (state == TITLE) {
			// �^�C�g�����
			textSize(80);
			fill(255, 255, 0);
			text("SHOOTING GAME", 600,500);
			textSize(40);
			fill(255);
			text("SPACE�ŃX�^�[�g", 600, 600);
			text("ENTER�Ń��j���[�ɖ߂�", 600, 700);
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
			ss.str("");  // ��������N���A
			ss << "Enemy HP: " << enemy->hp;
			text(ss.str().c_str(), 50, 120);
			if (player->hp <= 0) {
				text("GAME OVER", 600, 600);
			}
			if (enemy->hp <= 0) {
				text("YOU WIN!", 600, 600);
			}
			textSize(35);
			fill(255, 255, 0);
			
			fill(255);
			text("SPACE: ����  W;��  A;��  S;��  D;�E  Z: �^�C�g���ɖ߂�  ENTER; ���j���[�ɖ߂�", 0, 1080);
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
			text("Z�Ń^�C�g���֖߂�@ENTER�Ń��j���[�ɖ߂�", 500, 700);

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
			text("Z�Ń^�C�g���֖߂�@ENTER�Ń��j���[�ɖ߂�", 500, 700);

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
