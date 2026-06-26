#pragma once
namespace GAME05 {
	//キャラクタクラスごとに持たせるデータ
	struct ANIM_DATA {
		int imgIdx = 0;//アニメーションの画像番号
		float elapsedTime = 0;//前の画像に切り替わってからの経過時間
		float interval = 0.1f;//画像を切り替える間隔。単位は秒。デフォルトは0.1秒。
		void reset() { imgIdx = 0; elapsedTime = 0; }//アニメーションを最初からやり直すときに呼び出す関数
	};

	class ANIM {
	private:
		int NumImgs = 0;//アニメーションを構成する画像の数
		int* Imgs = 0;//アニメーションを構成する画像の配列
		bool LoopFlag = true;//ループするかどうかのフラグ。trueのとき、アニメーションはループする。falseのとき、アニメーションは1回だけ再生される。
	public:
		ANIM();//引数なしのコンストラクタは、load関数で画像を読み込むために用意している
		ANIM(const char* pathName);//引数ありのコンストラクタは、引数で指定したパスから画像を読み込むために用意している
		~ANIM();//アニメーションで使用している画像を開放するためのデストラクタ
		void load(const char* pathName);//指定したパスから画像を読み込む関数
		void divideRow(int imgIdx, int row, int cols, int w, int h);//指定した画像を、横にcols個、縦に1個の合計cols個の画像に分割する関数。rowは0から始まる。
		void divide(const char* filename, int cols, int rows, int w, int h);//指定したファイルから画像を分割する関数
		void draw(ANIM_DATA* animData, float px, float py, float angle = 0, float scale = 1);//アニメーションを描画する関数。animDataはアニメーションの状態を表す構造体へのポインタ。px, pyは描画位置、angleは回転角度、scaleは拡大率。
		void noLoop() { LoopFlag = false; }//ループしないようにする関数
		bool end(const ANIM_DATA& data) { return data.imgIdx >= NumImgs; }//アニメーションが最後まで再生されたかどうかを返す関数。ループしないときに使用する。
	};
}