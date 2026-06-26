#include"GAME.h"
#include"GAME05.h"
#include"CONTAINER.h"
#include"CHARACTER.h"
#include"PLAYER.h"
#include"PLAYER_BULLET.h"
#include"SURAIMU.h"
#include"TREE.h"
#include"TREE_BULLET.h"
#include"BOSS.h"
#include"BOSS_BULLET.h"
#include"CHARACTER_MANAGER.h"
namespace GAME05 {
    CHARACTER_MANAGER::CHARACTER_MANAGER(class GAME_* game) :
        GAME_OBJECT(game) {}//コンストラクタ
    CHARACTER_MANAGER::~CHARACTER_MANAGER() {//デストラクタ
        for (int i = 0; i < Total; i++) {
            delete Characters[i];
        }
        delete[] Characters;
    }
    void CHARACTER_MANAGER::create() {//キャラの初期設定を行う関数
        CharaMng = game()->container()->data().charaMng;

        Total = 0;
        Total += CharaMng.numPlayers;
        Total += CharaMng.numPlayerBullets;
        Total += CharaMng.numSuraimus;
        Total += CharaMng.numTrees;
        Total += CharaMng.numTreeBullets;
        Total += CharaMng.numBoss;
        Total += CharaMng.numBossBullets;
        Characters = new CHARACTER * [Total];

        Player = new PLAYER(game());
        int i, j = 0;
        for (i = 0; i < CharaMng.numPlayers; i++)       Characters[j++] = Player;
        for (i = 0; i < CharaMng.numPlayerBullets; i++) Characters[j++] = new PLAYER_BULLET(game());
        for (i = 0; i < CharaMng.numSuraimus; i++)      Characters[j++] = new SURAIMU(game());
        for (i = 0; i < CharaMng.numTrees; i++)          Characters[j++] = new TREE(game());
        for (i = 0; i < CharaMng.numTreeBullets; i++)    Characters[j++] = new TREE_BULLET(game());
        for (i = 0; i < CharaMng.numBoss; i++)          Characters[j++] = new BOSS(game());
        for (i = 0; i < CharaMng.numBossBullets; i++)    Characters[j++] = new BOSS_BULLET(game());

        for (int i = 0; i < Total; i++) {
            Characters[i]->create();
        }
    }
    void CHARACTER_MANAGER::init() {//キャラの初期化を行う関数
        for (int i = 0; i < Total; i++) {
            Characters[i]->init();
        }
    }
    void CHARACTER_MANAGER::appear(char charaId, float wx, float wy, float vx, float vy) {//キャラを出現させる関数
        // charaIdで指定されたキャラを出現させる
        for (int i = 0; i < Total; i++) {
            if (Characters[i]->charaId() == charaId) {
                if (Characters[i]->hp() <= 0) {
                    Characters[i]->appear(wx, wy, vx, vy);
                    break;
                }
            }
        }
    }
    void CHARACTER_MANAGER::update() {//キャラの更新を行う関数
        for (int i = 0; i < Total; i++) {
            if (Characters[i]->hp() > 0) {
                Characters[i]->update();
            }
        }
        //キャラとキャラの当たり判定---------------------------------------------------
        for (int i = 0; i < Total - 1; i++) {
            if (Characters[i]->hp() == 0) {
                continue;// ←ここでi++に戻る
            }
            for (int j = i + 1; j < Total; j++) {
                if (Characters[j]->hp() == 0) {
                    continue;// ←ここでj++に戻る
                }
                //仲間どうしは当たり判定しない
                if (Characters[i]->groupId() == Characters[j]->groupId()) {
                    continue;// ←ここでj++に戻る
                }
                //当たり判定
                if (Characters[i]->wLeft() < Characters[j]->wRight() &&
                    Characters[j]->wLeft() < Characters[i]->wRight() &&
                    Characters[i]->wTop() < Characters[j]->wBottom() &&
                    Characters[j]->wTop() < Characters[i]->wBottom()) {
                    //当たった
                    Characters[i]->damage();
                    Characters[j]->damage();
                }
            }
        }
    }
    void CHARACTER_MANAGER::draw() {//キャラの描画を行う関数
        for (int i = 0; i < Total; i++) {
            if (Characters[i]->hp() > 0) {
                Characters[i]->draw();
            }
        }
    }
}