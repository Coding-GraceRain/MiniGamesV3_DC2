#pragma once
#include"GAME_OBJECT.h"
#include"../../libOne/inc/COLOR.h"
#include"ANIMS.h"
namespace GAME05 {
	class CHARACTER :
		public GAME_OBJECT
	{
	public:
		struct DATA {
			//複数アニメor単体アニメor静止画を使用する
			//複数アニメーション
			class ANIMS* anims = nullptr;//複数アニメーションを使用する場合はanimsを使用する
			int animId = 0;
			//単体アニメーション
			class ANIM* anim = nullptr;//単体アニメーションを使用する場合はanimwを使用する
			ANIM_DATA animData;//単体アニメーションのデータ
			//静止画
			int img = 0;//静止画を使用する場合はimgを使用する
			//合成色
			COLOR color;

			char charaId = 0;//マップデータ上でのキャラの識別子
			int groupId = 0;//グループ識別子。味方同士、敵同士は同じグループIDにする。衝突判定のとき、グループIDが違うキャラ同士だけ当たり判定を行うようにするため。
			float wx = 0;//ワールド座標
			float wy = 0;//ワールド座標
			float vx = 0;//移動ベクトル
			float vy = 0;//移動ベクトル
			float speed = 0;//移動速度。移動ベクトルの長さをこの値にする。
			float angle = 0;//回転角度
			float scale = 1;//拡大率

			int hp = 0;//体力
			float offsetLeft = 0;//当たり判定用のオフセット。キャラの中心を基準にして、左にどれだけオフセットするか。
			float offsetTop = 0;//当たり判定用のオフセット。キャラの中心を基準にして、上にどれだけオフセットするか。
			float offsetRight = 0;//当たり判定用のオフセット。キャラの中心を基準にして、右にどれだけオフセットするか。
			float offsetBottom = 0;//当たり判定用のオフセット。キャラの中心を基準にして、下にどれだけオフセットするか。
		};
	protected:
		DATA Chara;//キャラのデータ
	public:
		CHARACTER(class GAME_* game);//コンストラクタ
		virtual void create();//キャラの初期設定を行う関数
		virtual void init();//キャラの初期化を行う関数
		virtual void appear(float wx, float wy, float vx, float vy);//キャラを出現させる関数
		virtual void update();//キャラの更新を行う関数
		virtual void draw();//キャラの描画を行う関数
		virtual void damage();//キャラがダメージを受けるときの関数
		int   hp() { return Chara.hp; }//体力を返す関数
		int   groupId() { return Chara.groupId; }//グループIDを返す関数
		float wx() const { return Chara.wx; }
		float wy() const { return Chara.wy; }
		char  charaId() { return Chara.charaId; }//マップデータ上でのキャラの識別子を返す関数
		float wLeft() { return Chara.wx + Chara.offsetLeft; }//ワールド座標の左端を返す関数
		float wTop() { return Chara.wy + Chara.offsetTop; }//ワールド座標の上端を返す関数
		float wRight() { return Chara.wx + Chara.offsetRight; }//ワールド座標の右端を返す関数
		float wBottom() { return Chara.wy + Chara.offsetBottom; }//ワールド座標の下端を返す関数
		void setImgIdx(int i) { Chara.animData.imgIdx = i; }//アニメーションの画像番号をセットする関数
	};
}