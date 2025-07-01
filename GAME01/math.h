#pragma once
#include"GAME01.h"
#include "../../libOne/inc/libOne.h"
#include "../MAIN/MAIN.h"
#include <cstdlib>
namespace GAME01 {
	class MATH
	{
	private:
		int Ma, Mb,Mc,Md,Me,Mf,Mg,Mh,Mi,Mj,Mk,Ml,Manser,Manser2,Manser3,Manser4,Manser5,Manser6;
		int select1 = 0;
		char inputBufferA[32] = ""; // 入力された文字列（最大31文字＋終端）
		int inputLenA = 0;
		char inputStrA[32];
		int valueA;
		bool anser1Generated;
		bool anser2Generated;
		bool anser3Generated;
		bool anser4Generated;
		bool anser5Generated;
		bool anser6Generated;
		bool answerChecked = false;
		bool answerCorrect = false;
	public:
		void game();
		void proc();
		void anser1();
		void anser2();
		void anser3();
		void anser4();
		void anser5();
		void anser6();
		void key();
		void data();
		MATH* math1();
		MATH* math2();
		MATH* math3();
		MATH* math4();
		MATH* math5();
		MATH* math6();
	};
	
}