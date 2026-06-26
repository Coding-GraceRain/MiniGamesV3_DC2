#pragma once
#include"ANIM.h"
namespace GAME05 {
	class ANIMS {
	private:
		int NumAnims = 0;
		class ANIM** Anims = 0;
	public:
		ANIMS();//引数なしのコンストラクタ
		ANIMS(const char* path);//ファイル名を引数にとるコンストラクタ
		ANIMS(const char* fileName, int cols, int rows, int w, int h);//ファイル名と分割方法を引数にとるコンストラクタ
		~ANIMS();//デストラクタ
		void load(const char* path);//ファイル名を引数にとるload関数
		void load(const char* fileName, int cols, int rows, int w, int h);//ファイル名と分割方法を引数にとるload関数
		//getter
		class ANIM* anim(int animIdx);//animIdx番目のANIMを返す関数
	};
}

