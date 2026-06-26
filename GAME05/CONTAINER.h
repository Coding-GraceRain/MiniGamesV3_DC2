#pragma once
#include"TITLE.h"
#include"STAGE.h"
#include"FADE.h"
#include"MAP.h"
#include"PLAYER.h"
#include"SURAIMU.h"
#include"TREE.h"
#include"BOSS.h"
#include"LAYER.h"
#include"LAYER2.h"
#include"CHARACTER_MANAGER.h"
namespace GAME05 {
	class CONTAINER
	{
	private:
		struct DATA {
			TITLE::DATA title;//タイトル全体で使用するデータ
			STAGE::DATA stage;//ステージ全体で使用するデータ
			FADE::DATA fade;//フェード全体で使用するデータ
			MAP::DATA map;//マップ全体で使用するデータ
			LAYER::DATA layer;//レイヤー全体で使用するデータ
			LAYER2::DATA layer2;//レイヤー2全体で使用するデータ
			CHARACTER::DATA playerChara;//プレイヤー全体で使用するデータ
			PLAYER::DATA player;//プレイヤーの全体で使用するデータ
			CHARACTER::DATA playerBulletChara;
			CHARACTER::DATA suraimuChara;//スライム全体で使用するデータ
			SURAIMU::DATA suraimu;//スライムの全体で使用するデータ
			CHARACTER::DATA treeChara;
			TREE::DATA tree;
			CHARACTER::DATA treeBulletChara;
			CHARACTER::DATA bossChara;
			BOSS::DATA boss;
			CHARACTER::DATA bossBulletChara;
			CHARACTER_MANAGER::DATA charaMng;//キャラ管理全体で使用するデータ
		};
		DATA Data;
		void CreateData();//ゲーム全体で使用するデータの作成を行う関数
		void LoadGraphics();//ゲーム全体で使用するグラフィックの読み込みを行う関数
	public:
		~CONTAINER();//ゲーム全体で使用するデータの開放を行う関数
		void load();//ゲーム全体で使用するデータの作成とグラフィックの読み込みを行う関数
		const DATA& data() { return Data; }
	};
}

