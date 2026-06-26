#pragma once
#include "CHARACTER.h"
namespace GAME05 {
	class PLAYER :
		public CHARACTER
	{
	public:
		struct DATA {
			int rightAnimId = 0;//右向きのアニメーションID
			int leftAnimId = 1;//左向きのアニメーションID
			int jumpFlag = 0;//ジャンプの状態を表すフラグ。0はジャンプしていない状態、1はジャンプ中の状態、2は落下中の状態。
			float curWx = 0;//移動前のワールド座標。マップチップとの当たり判定のときに使用する。
			float initVecUp = 0;//ジャンプの初期速度（上方向）
			float initVecDown = 0;//落下の初期速度（下方向）
			float gravity = 0;//重力
			char bulletCharaId = 0;
			float bulletOffsetX = 0;
		};
	private:
		DATA Player;//プレイヤーのデータ
		enum class STATE { STRUGGLING, DIED, FALL, SURVIVED };//プレイヤーの状態を表す列挙型。STRUGGLINGはもがいている状態、DIEDは死亡した状態、FALLは落ちた状態、SURVIVEDはステージクリアした状態。
		STATE State = STATE::STRUGGLING;//最初はもがいている状態
	public://   
		PLAYER(class GAME_* game) :CHARACTER(game) {}
		void create();//プレイヤーの初期設定を行う関数
		void appear(float wx, float wy, float vx, float vy);//プレイヤーを出現させる関数
		void update();//プレイヤーの更新を行う関数
	private:
		void Launch();
		void Move();//プレイヤーの移動を行う関数
		void CollisionWithMap();//マップとの衝突判定を行う関数
		void CheckState();//プレイヤーの状態をチェックする関数
	public:
		void damage();//プレイヤーにダメージを与える関数
		bool died();//プレイヤーが死亡したかチェックする関数
		bool survived();//プレイヤーがステージクリアしたかチェックする関数
		float overCenterVx();//センターを越えた水平方向の速度を求める関数
	};
}