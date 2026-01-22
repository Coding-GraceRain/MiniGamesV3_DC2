#include "../../libOne/inc/libOne.h"
#include "../MAIN/MAIN.h"
#include "GAME01.h"
#include "kanji.h"
#include"windows.h"
#include<cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
namespace GAME01 {
	int KANJI::cont = 0;
	void KANJI::game() {
		clear(0, 0, 64);
		textSize(55);
		fill(255, 255, 255);
		text("難易度を選んでください。※「」内のキーを入力すると進みます。", 20, 200);
		text("", 20, 280);
		text("[←]キーでメニューに戻る", 90, 1000);
		fill(100, 120, 105);
		rect(10, 400, 970, 200);
		/*fill(120, 110, 60);
		rect(510, 400, 370, 200);
		fill(185, 90, 100);
		rect(1010, 400, 370, 200);
		fill(145, 15, 105);
		rect(1510, 400, 370, 200);*/
		textSize(45);
		fill(0, 0, 0);
		text("★☆☆☆☆「→」", 20, 530);
		/*text("★★☆☆☆「O」", 520, 530);
		text("★★★☆☆「I」", 1020, 530);
		text("★★★★☆「U」", 1520, 530);
		fill(150, 170, 120);
		rect(510, 670, 870, 200);
		textSize(40);
		fill(255, 255, 255);
		text("高難易度★★★★★「Y」", 510, 750);*/
	}
	void KANJI::Kanser1() {
		if (!Kanser1Generated && kanjiCount > 0) {
			currentKanji = random(0, kanjiCount - 1);
			Kanser1Generated = true;
		}
		fill(255, 255, 255);
		clear(0, 0, 64);
		textSize(80);
		text("上の漢字の読み方を答えてください。", 20, 700);
		text("※回答を入力しないと次に進めません※", 20, 800);
		text(kanji[currentKanji].yomi, 700, 600); //debug
		textSize(55);
		text("[←]キーで中断", 90, 1000);
		text("[↓]キーで1文字削除", 600, 1000);
		char buf[64];
		sprintf_s(buf, "yomi ptr = %p", kanji[currentKanji].yomi);
		text(buf, 50, 900);
		char buf2[64];
		sprintf_s(buf2, "currentKanji=%d", currentKanji);
		text(buf2, 50, 850);
		fill(255, 255, 0);
		if (kanjiCount > 0) {
			image(kanji[currentKanji].img, 120, 100);
	    }
		fill(255, 255, 0);
	}
	/*void KANJI::Kanser2() {
		fill(255, 255, 255);
		clear(0, 0, 64);
		textSize(80);
		text("上の漢字の読み方を答えてください。", 20, 200);
		text("※回答を入力しないと次に戻れません※", 20, 700);
		fill(255, 255, 0);
		text("test2", 730, 100);
	}
	void KANJI::Kanser3() {
		fill(255, 255, 255);
		clear(0, 0, 64);
		textSize(80);
		text("上の漢字の読み方を答えてください。", 20, 200);
		text("※回答を入力しないと次に戻れません※", 20, 700);
		fill(255, 255, 0);
		text("test3", 730, 100);
	}
	void KANJI::Kanser4() {
		fill(255, 255, 255);
		clear(0, 0, 64);
		textSize(80);
		text("上の漢字の読み方を答えてください。", 20, 200);
		text("※回答を入力しないと次に戻れません※", 20, 700);
		fill(255, 255, 0);
		text("test4", 730, 100);
	}
	void KANJI::Kanser5() {
		fill(255, 255, 255);
		clear(0, 0, 64);
		textSize(80);
		text("上の漢字の読み方を答えてください。", 20, 200);
		text("※回答を入力しないと次に戻れません※", 20, 700);
		fill(255, 255, 0);
		text("test5", 730, 100);
	}
	void KANJI::Kanser6() {
		fill(255, 255, 255);
		clear(0, 0, 64);
		textSize(80);
		text("上の漢字の読み方を答えてください。", 20, 200);
		text("※回答を入力しないと次に戻れません※", 20, 700);
		fill(255, 255, 0);
		text("test6", 730, 100);
	}*/
	void KANJI::romajiToKana(const char* src, char* dst) {

		struct RomajiKana {
			const char* r;
			const char* k;
		};

		static const RomajiKana table[] = {
			// 母音
			{"a","あ"},{"i","い"},{"u","う"},{"e","え"},{"o","お"},
			// K
			{"ka","か"},{"ki","き"},{"ku","く"},{"ke","け"},{"ko","こ"},
			{"kya","きゃ"},{"kyu","きゅ"},{"kyo","きょ"},
			// S
			{"sa","さ"},{"shi","し"},{"su","す"},{"se","せ"},{"so","そ"},
			{"sha","しゃ"},{"shu","しゅ"},{"sho","しょ"},
			// T
			{"ta","た"},{"ti","ち"},{"tu","つ"},{"te","て"},{"to","と"},
			{"tya","ちゃ"},{"tyu","ちゅ"},{"tyo","ちょ"},
			// N
			{"na","な"},{"ni","に"},{"nu","ぬ"},{"ne","ね"},{"no","の"},
			{"nya","にゃ"},{"nyu","にゅ"},{"nyo","にょ"},
			{"n","ん"},
			// H
			{"ha","は"},{"hi","ひ"},{"fu","ふ"},{"he","へ"},{"ho","ほ"},
			{"hya","ひゃ"},{"hyu","ひゅ"},{"hyo","ひょ"},
			// M
			{"ma","ま"},{"mi","み"},{"mu","む"},{"me","め"},{"mo","も"},
			{"mya","みゃ"},{"myu","みゅ"},{"myo","みょ"},
			// Y
			{"ya","や"},{"yu","ゆ"},{"yo","よ"},
			// R
			{"ra","ら"},{"ri","り"},{"ru","る"},{"re","れ"},{"ro","ろ"},
			{"rya","りゃ"},{"ryu","りゅ"},{"ryo","りょ"},
			// W
			{"wa","わ"},{"wo","を"},
			// G
			{"ga","が"},{"gi","ぎ"},{"gu","ぐ"},{"ge","げ"},{"go","ご"},
			// Z
			{"za","ざ"},{"zi","じ"},{"zu","ず"},{"ze","ぜ"},{"zo","ぞ"},
			// D
			{"da","だ"},{"de","で"},{"do","ど"},
			// B
			{"ba","ば"},{"bi","び"},{"bu","ぶ"},{"be","べ"},{"bo","ぼ"},
			// P
			{"pa","ぱ"},{"pi","ぴ"},{"pu","ぷ"},{"pe","ぺ"},{"po","ぽ"},
		};
		// 最長一致で検索
		for (const auto& e : table) {
			if (strcmp(src, e.r) == 0) {
				strcpy_s(dst, 64, e.k);
				return;
			}
		}
		// 未変換はそのまま
		strcpy_s(dst, 64, src);
	}

	void KANJI::loadKanjiImages() {
		if ( kanjiCount > 0) return;
		kanji[0] = { loadImage("..\\MAIN\\assets\\game01\\kanji1.png"), "zigoku" };
		kanji[1] = { loadImage("..\\MAIN\\assets\\game01\\kanji2.png"), "ekohiiki" };
		kanji[2] = { loadImage("..\\MAIN\\assets\\game01\\kanji3.png"), "shinrei" };
		kanji[3] = { loadImage("..\\MAIN\\assets\\game01\\kanji4.png"), "iseki" };
		kanji[4] = { loadImage("..\\MAIN\\assets\\game01\\kanji5.png"), "tukigime" };
		kanji[5] = { loadImage("..\\MAIN\\assets\\game01\\kanji6.png"), "doutoku" };
		kanji[6] = { loadImage("..\\MAIN\\assets\\game01\\kanji7.png"), "unpan" };
		kanji[7] = { loadImage("..\\MAIN\\assets\\game01\\kanji8.png"), "haguku" };
		kanjiCount = 8;
	}

	/*void KANJI::loadKanjiImages() {
		if (kanjiCount > 0) return;

		kanji[0].img = loadImage("..\\MAIN\\assets\\game01\\kanji1.png");
		strcpy_s(kanji[0].yomi, "zigoku");

		kanji[1].img = loadImage("..\\MAIN\\assets\\game01\\kanji2.png");
		strcpy_s(kanji[1].yomi, "ekohiiki");

		kanji[2].img = loadImage("..\\MAIN\\assets\\game01\\kanji3.png");
		strcpy_s(kanji[2].yomi, "shinrei");

		kanji[3].img = loadImage("..\\MAIN\\assets\\game01\\kanji4.png");
		strcpy_s(kanji[3].yomi, "iseki");

		kanji[4].img = loadImage("..\\MAIN\\assets\\game01\\kanji5.png");
		strcpy_s(kanji[4].yomi, "tukigime");

		kanji[5].img = loadImage("..\\MAIN\\assets\\game01\\kanji6.png");
		strcpy_s(kanji[5].yomi, "doutoku");

		kanji[6].img = loadImage("..\\MAIN\\assets\\game01\\kanji7.png");
		strcpy_s(kanji[6].yomi, "unpan");

		kanji[7].img = loadImage("..\\MAIN\\assets\\game01\\kanji8.png");
		strcpy_s(kanji[7].yomi, "haguku");
		kanjiCount = 8;
	}*/
	KANJI* KANJI::kanji1() {
		static KANJI kanjiinstance1;
		kanjiinstance1.loadKanjiImages();
		return &kanjiinstance1;
	}
	/*KANJI* KANJI::kanji2(){
		static KANJI kanjiInstance1;
		return &kanjiInstance1;
	}
	KANJI* KANJI::kanji3(){
		static KANJI kanjiInstance1;
		return &kanjiInstance1;
	}
	KANJI* KANJI::kanji4(){
		static KANJI kanjiInstance1;
		return &kanjiInstance1;
	}
	KANJI* KANJI::kanji5(){
		static KANJI kanjiInstance1;
		return &kanjiInstance1;
	}
	KANJI* KANJI::kanji6(){
		static KANJI kanjiInstance1;
		return &kanjiInstance1;
	}*/

	void KANJI::triming(char* s) {
		int len = strlen(s);
		while (len > 0 && (s[len - 1] < 'a' || s[len - 1] > 'z')) {
			s[len - 1] = '\0';
			len--;
		}
	}

	void KANJI::initialize() {

		// 問題状態
		currentKanji = 0;
		Kanser1Generated = false;

		// 入力状態
		memset(inputStrB, 0, sizeof(inputStrB));
		memset(displayStr, 0, sizeof(displayStr));
		inputLenB = 0;

		// 判定状態
		KanswerChecked = false;
		KanswerCorrect = false;

		kanjiCount = 0;
	}

	void KANJI::proc() {
		if (kanjiCount == 0) {
			loadKanjiImages();
			currentKanji = random(0, kanjiCount - 1);
		}
		if (select2 == 0) {
			game();
			if (isTrigger(KEY_RIGHT)) {
				kanji1();
				select2 = 1;
			}
			/*if (isTrigger(KEY_UP)) {
				kanji2();
				select2 = 2;
			}
			if (isTrigger(KEY_DOWN)) {
				kanji3();
				select2 = 3;
			}
			if (isTrigger(KEY_)) {
				kanji4();
				select2 = 4;
			}
			if (isTrigger(KEY_)) {
				kanji5();
				select2 = 5;
			}
			if (isTrigger(KEY_)) {
				kanji6();
				select2 = 6;
			}*/
		}
		else if (select2 == 1) {
			KANJI* k1 = KANJI::kanji1();
			k1->Kanser1();
			key();
			romajiToKana(inputStrB, displayStr);
			textSize(80);
			//入力表示
			fill(255, 255, 0);
			text(inputStrB, 200, 300);
			/*text(displayStr, 200, 400);*/
			if (isTrigger(KEY_LEFT)) {
				cont = 1;
			}
			if (!KanswerChecked) {
				// まだ判定していない
				if (isTrigger(KEY_SPACE)) {
					if (inputStrB[0] != '\0') {
						triming(inputStrB);
						KanswerCorrect = strcmp(inputStrB, kanji[currentKanji].yomi) == 0;
						KanswerChecked = true;
					}
				}
			}
			else {
				// 判定済み → 結果表示
				textSize(50);

				if (KanswerCorrect) {
					text("正解！", 700, 400);
					text("Enterで次の問題へ", 700, 500);
					text("Shiftでメニューに戻る", 700, 600);
					cont = 0;
				}
				else {
					text("不正解！", 700, 400);
					text("Enterで次の問題へ", 700, 500);
					text("Shiftでメニューに戻る", 700, 600);
				}

				// 次の問題
				if (isTrigger(KEY_ENTER)) {
					KANJI::kanji1()->Kanser1Generated = false;
					//currentKanji = random(0, kanjiCount - 1); // ★追加
					memset(inputStrB, 0, sizeof(inputStrB));
					inputLenB = 0;
					KanswerChecked = false;
					KanswerCorrect = false;
				}

				// メニューへ戻る
				if (isTrigger(KEY_SHIFT)) {
					KANJI::kanji1()->initialize();
					select2 = 0;   // ← KANJIメニューに戻る
				}
			}
		}
			/*else if (select2 == 2) {
				KANJI* k2 = KANJI::kanji2();
				k2->Kanser2();
				if (isTrigger(KEY_LEFT)) {
					cont = 1;
				}
			}
			else if (select2 == 3) {
				KANJI* k3 = KANJI::kanji3();
				k3->Kanser3();
				if (isTrigger(KEY_LEFT)) {
					cont = 1;
				}
			}
			else if (select2 == 4) {
				KANJI* k4 = KANJI::kanji4();
				k4->Kanser4();
				if (isTrigger(KEY_LEFT)) {
					cont = 1;
				}
			}
			else if (select2 == 5) {
				KANJI* k5 = KANJI::kanji5();
				k5->Kanser5();
				if (isTrigger(KEY_LEFT)) {
					cont = 1;
				}
			}
			else if (select2 == 6) {
				KANJI* k6 = KANJI::kanji6();
				k6->Kanser6();
				if (isTrigger(KEY_LEFT)) {
					cont = 1;
				}
			}*/
			textSize(50);
			fill(255, 255, 255);
			fill(255, 255, 255);
		}

		void KANJI::key() {
			//1文字削除（KEY_DOWN）
			if (isTrigger(KEY_DOWN)) {
				if (inputLenB > 0) {
					inputLenB--;
					inputStrB[inputLenB] = '\0';
				}
				return;
			}
			if (inputLenB >= 31) return;

			// キーコードと文字の対応表
			const INPUT_CODE keys[26] = {
				KEY_A, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F,
				KEY_G, KEY_H, KEY_I, KEY_J, KEY_K, KEY_L,
				KEY_M, KEY_N, KEY_O, KEY_P, KEY_Q, KEY_R,
				KEY_S, KEY_T, KEY_U, KEY_V, KEY_W, KEY_X,
				KEY_Y, KEY_Z
			};

			for (int i = 0; i < 26; i++) {
				if (isTrigger(keys[i])) {
					inputStrB[inputLenB++] = 'a' + i;
					inputStrB[inputLenB] = '\0'; // 文字列終端
					break;
				}
			}
		}
	}