#include "../../libOne/inc/input.h"
#include "../../libOne/inc/graphic.h"
#include "../../libOne/inc/mathUtil.h"
#include "../MAIN/MAIN.h"
#include "GAME06.h"
#include "PLAYER.h"
#include "ENEMY.h"
#include "BULLET.h"
#include "PLAYER_BULLET.h"
#include "ENEMY_BULLET.h"

namespace GAME06
{
	int GAME::create()
	{
		Player = new PLAYER();
		Enemy = new ENEMY();
		for (int i = 0; i < TOTAL_BULLETS; ++i) {
			if (i < PLAYER_BULLETS) {
				Bullet[i] = new PLAYER_BULLET();
			}
			else {
				Bullet[i] = new ENEMY_BULLET();
			}
		}
		return 0;
	}

	void GAME::destroy()
	{
		for (int i = TOTAL_BULLETS - 1; i >= 0; --i) {
			delete Bullet[i];
		}
		delete Enemy;
		delete Player;
	}

	void GAME::init() {
		Player->init();
		Enemy->init();
		for (int i = 0; i < TOTAL_BULLETS; ++i) {
			Bullet[i]->init();
		}
	}

	bool GAME::collision(class PLAYER* p, class BULLET* eb) {
		float pLeft = p->px() - p->w() / 2;
		float pRight = p->px() + p->w() / 2;
		float pTop = p->py() - p->h() / 2;
		float pBottom = p->py() + p->h() / 2;
		float ebLeft = eb->px() - eb->w() / 2;
		float ebRight = eb->px() + eb->w() / 2;
		float ebTop = eb->py() - eb->h() / 2;
		float ebBottom = eb->py() + eb->h() / 2;
		if (pLeft > ebRight || pRight < ebLeft ||
			pTop > ebBottom || pBottom < ebTop) {
			return false;
		}
		else { 
			return true; 
		}
	}

	bool GAME::collision(class ENEMY* e, class BULLET* pb) {
		float eLeft = e->px() - e->w() / 2;
		float eRight = e->px() + e->w() / 2;
		float eTop = e->py() - e->h() / 2;
		float eBottom = e->py() + e->h() / 2;
		float pbLeft = pb->px() - pb->w() / 2;
		float pbRight = pb->px() + pb->w() / 2;
		float pbTop = pb->py() - pb->h() / 2;
		float pbBottom = pb->py() + pb->h() / 2;
		if (eLeft > pbRight || eRight < pbLeft ||
			eTop > pbBottom || eBottom < pbTop) {
			return false;
		}
		else {
			return true;
		}
	}

	void GAME::proc()
	{
		clear(60);
		//操作方法の説明
		textSize(40);
		fill(255, 255, 0);
		text("左へ移動：Aキー", 0, 40);
		text("右へ移動：Dキー", 0, 80);
		text("攻撃　　：SPACEキー", 0, 120);
		//結果が出るまで実行する
		if (Player->hp() > 0 && Enemy->hp() > 0) {
			//データを更新する
			Player->update();
			Enemy->update();
			//プレイヤーの弾の位置を設定する
			if (isTrigger(KEY_SPACE)) {
				for (int i = 0; i < PLAYER_BULLETS; ++i) {
					if (Bullet[i]->flag() == false) {
						Bullet[i]->flag() = true;
						Bullet[i]->px() = Player->px();
						Bullet[i]->py() = Player->py() + Player->ofsY();
						break;
					}
				}
			}
			//6フレームに一回実行する
			if (Counter % (FPS / 10) == 0) {
				//敵の弾の位置と速度を設定する
				for (int i = PLAYER_BULLETS; i < TOTAL_BULLETS; ++i) {
					if (Bullet[i]->flag() == false) {
						Bullet[i]->flag() = true;
						Bullet[i]->px() = Enemy->px();
						Bullet[i]->py() = Enemy->py() + Enemy->ofsY();
						float dx = Player->px() - Bullet[i]->px();
						float dy = Player->py() - Bullet[i]->py();
						float distance = Sqrt(dx * dx + dy * dy);
						if (distance != 0) {
							Bullet[i]->vx() = dx / distance * 12;
							Bullet[i]->vy() = dy / distance * 12;
						}
						break;
					}
				}
			}
			//カウンターを進める
			++Counter;
			//カウンターをリセットする
			if (Counter > FPS)Counter = 0;
			//発射可能な全ての弾の位置を更新する
			for (int i = 0; i < TOTAL_BULLETS; ++i) {
				Bullet[i]->shot();
			}
			//ダメージを与える
			for (int i = 0; i < PLAYER_BULLETS; ++i) {
				if (collision(Enemy, Bullet[i])) {
					if (Enemy->hp() > 0) {
						Enemy->hp()--;
					}
				}
			}
			for (int i = PLAYER_BULLETS; i < TOTAL_BULLETS; ++i) {
				if (collision(Player, Bullet[i])) {
					if (Player->hp() > 0) {
						Player->hp()--;
					}
				}
			}
		}
		//結果を表示する
		if (Enemy->hp() <= 0 && Player->hp() > 0) {
			textSize(200);
			fill(0, 255, 0);
			text("WIN!!", 580, 540);
			fill(255, 0, 0);
			textSize(50);
			text("SPACEキーでリスタート", 580, 740);
			if(isTrigger(KEY_SPACE)){
				init();
			}
		}
		if (Player->hp() <= 0) {
			textSize(200);
			fill(0, 200, 200);
			text("LOSE", 580, 540);
			textSize(50);
			text("SPACEキーでリスタート", 580, 740);
			if (isTrigger(KEY_SPACE)) {
				init();
			}
		}
		//描画
		Player->draw();
		Enemy->draw();
		for (int i = 0; i < TOTAL_BULLETS; ++i) {
			Bullet[i]->draw();
		}
		textSize(40);
		fill(255, 255, 0);
		text("ENTERキーでメニューに戻る", 0, 1080);
		if (isTrigger(KEY_ENTER)) {
			main()->backToMenu();
		}
	}
}
