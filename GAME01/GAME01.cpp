#include "../../libOne/inc/libOne.h"
#include "../MAIN/MAIN.h"
#include "GAME01.h"
#include "time.h"
#include"math.h"
namespace GAME01
{
	int GAME::create()  //1回限り
	{
		file();
		return 0;
	}

	int GAME::file()
	{
		FILE* file2;
		if (fopen_s(&file2, "playcount.txt", "r") != 0) {
			return 0;
		}
		else {
			if (fscanf_s(file2, "%d", &c2) != 1) {
				fclose(file2);
				return 0;
			}
			fclose(file2);
		}
		return 0;
	}

	void GAME::destroy()
	{

	}

	MATH* GAME::math()
	{
		static MATH mathInstance;
		return &mathInstance;
	}

	void GAME::counter()
	{
		FILE* file2;
		//総プレイ回数カウント
		c2++;
		// 結果をファイルに書き込む
		if (fopen_s(&file2, "playcount.txt", "w") == 0) {
			fprintf_s(file2, "%d", c2);  // 新しい値をファイルに書き込む
			fclose(file2);  // ファイルを閉じ
		}
	}

	void GAME::draw()
	{
		clear(0, 0, 64);
		textSize(80);
		fill(255, 255, 0);
		text("脳トレ", 820, 100);
		textSize(50);
		fill(255);
		text("ENTERキーでメニューに戻る", 620, 980);
		fill(0, 255, 0);
		rect(100, 200, 800, 300);
		textSize(60);
		fill(0);
		text("四則演算/「M」KEYを押す", 100, 380);
		textSize(30);
		fill(255);
		text("制限時間内で四則の演算をするモードです。※不正解でも次に進めます。", 900, 380);
		return;
	}

	void GAME::proc() {
		if (currentScene== 0) {
			draw();
			if (isTrigger(KEY_M)) {
				currentScene = 1;
			}
			if (isTrigger(KEY_K)) {
				currentScene = 2;
			}
			if (isTrigger(KEY_ENTER)) {
				counter();
				main()->backToMenu();
			}
		}
		else if (currentScene == 1) {
			MATH* Imath = GAME::math();
			Imath->proc();
			if (isTrigger(KEY_LEFT)) {
				currentScene = 0;
			}
		}
	}
}

