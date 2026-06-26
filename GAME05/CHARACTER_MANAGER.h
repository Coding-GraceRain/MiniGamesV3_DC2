#pragma once
#include "GAME_OBJECT.h"
namespace GAME05 {
	class CHARACTER_MANAGER :
		public GAME_OBJECT
	{
	public:
		struct DATA {
			int numPlayers = 0;//プレイヤーの最大数
			int numPlayerBullets = 0;
			int numSuraimus = 0;//スライムの最大数
			int numTrees = 0;
			int numTreeBullets = 0;
			int numBoss = 0;
			int numBossBullets = 0;
			//int numExplosions = 0;
		};
	private:
		int Total = 0;//管理するキャラの総数
		DATA CharaMng;//キャラ管理のデータ
		class CHARACTER** Characters = nullptr;//キャラの配列
		class PLAYER* Player = nullptr;//最初のプレイヤーをPlayerとする
	public:
		CHARACTER_MANAGER(class GAME_* game);//コンストラクタ
		~CHARACTER_MANAGER();//デストラクタ
		void create();//キャラの初期設定を行う関数
		void init();//キャラの初期化を行う関数
		void appear(char charaId, float wx, float wy, float vx = 0, float vy = 0);//char charaIdで指定されたキャラを出現させる関数
		void update();//キャラの更新を行う関数
		void draw();//キャラの描画を行う関数
		class PLAYER* player() { return Player; }//プレイヤーを返す関数
	};
}