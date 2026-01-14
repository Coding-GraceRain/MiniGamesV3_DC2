#pragma once
#include"GAME01.h"
#include "../../libOne/inc/libOne.h"
#include "../MAIN/MAIN.h"
#include <cstdlib>
#include<cstring>
namespace GAME01 {
	struct KanjiData {
		int img;                // 画像ID
		const char* yomi;       // 正解の読み
	};
	class KANJI {
	private:
		int select2 = 0;
		static const int KANJI_MAX = 8;
		KanjiData kanji[KANJI_MAX];
		int kanjiCount = 0;
		int currentKanji = 0;
		char inputStrB[32] = "";    // 入力文字
		char displayStr[64] = "";
		int inputLenB = 0;
		bool decided = false;
		void loadKanjiImages();
		void romajiToKana(const char* src, char* dst);
		bool Kanser1Generated = false;
		bool Kanser2Generated;
		bool Kanser3Generated;
		bool Kanser4Generated;
		bool Kanser5Generated;
		bool Kanser6Generated;
		bool KanswerChecked = false;
		bool KanswerCorrect = false;
		int correctCount = 0;   // 今回の10問用カウンタ (0?10)
		int point = 0;          // 累計ポイント（保存される
	public:
		static int cont;
		void game();
		void Kanser1();
		void Kanser2();
		void Kanser3();
		void Kanser4();
		void Kanser5();
		void Kanser6();
		void key();
		void proc();
		KANJI* kanji1();
		KANJI* kanji2();
		KANJI* kanji3();
		KANJI* kanji4();
		KANJI* kanji5();
		KANJI* kanji6();
		int kanjiImg;   // ← 追加：漢字画像ID
	};
}