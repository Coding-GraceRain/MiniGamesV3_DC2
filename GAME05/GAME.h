#pragma once
namespace GAME05 {
	class GAME_ {
		//コンテナ
	private:
		class CONTAINER* Container = nullptr;//ゲーム全体で使用するデータとグラフィックを管理するクラス
	public:
		class CONTAINER* container() { return Container; };//ゲーム全体で使用するデータとグラフィックを管理するクラスを返す関数
		//シーン
	private:
		class TITLE* Title = nullptr;//タイトルシーンを管理するクラス
		class STAGE* Stage = nullptr;//ステージシーンを管理するクラス
		class SCENE* CurScene = nullptr;//現在のシーンを管理するクラス
		class FADE* Fade = nullptr;//フェードを管理するクラス
	public:
		class TITLE* title() { return Title; }//タイトルシーンを管理するクラスを返す関数
		class STAGE* stage() { return Stage; }//ステージシーンを管理するクラスを返す関数
		class FADE* fade() { return Fade; }//フェードを管理するクラスを返す関数
		void setCurScene(class SCENE* scene);//シーンを切り替える関数
		//キャラクタ
	private:
		class MAP* Map = nullptr;//マップを管理するクラス
		class CHARACTER_MANAGER* CharacterManager = nullptr;//キャラ管理を管理するクラス
		class LAYER* Layer = nullptr;//レイヤーを管理するクラス
		class LAYER2* Layer2 = nullptr;//レイヤー2を管理するクラス
	public:
		class MAP* map() { return Map; }//マップを管理するクラスを返す関数
		class CHARACTER_MANAGER* characterManager() { return CharacterManager; }//キャラ管理を管理するクラスを返す関数
		class LAYER* layer() { return Layer; }//レイヤーを管理するクラスを返す関数
		class LAYER2* layer2() { return Layer2; }//レイヤー2を管理するクラスを返す関数
	public:
		GAME_();//コンストラクタ
		~GAME_();//デストラクタ
		void run();//ゲームを実行する関数
		void proc();//ゲームの更新処理を行う関数
	};
}