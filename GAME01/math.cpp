#include "../../libOne/inc/libOne.h"
#include "../MAIN/MAIN.h"
#include "GAME01.h"
#include "math.h"
#include"windows.h"
#include<cstdlib>
#include"input2.h"
namespace GAME01 {
	void MATH::game()    /*�����_�����ǂݍ��݁��v�Z*/
	{
		clear(0, 0, 64);
		textSize(55);
		fill(255, 255, 255);
		text("���[�h��I��ł��������B���u�v���̃L�[����͂���Ɛi�݂܂��B",20, 200);
		text("[��]�L�[�Ń��j���[�ɖ߂�", 90, 1000);
		fill(0, 0, 255);
		rect(10, 400, 370, 200);
		fill(0, 255, 0);
		rect(510, 400, 370, 200);
		fill(255, 0, 0);
		rect(1010, 400, 370, 200);
		fill(125, 125, 125);
		rect(1510, 400, 370, 200);
		textSize(70);
		fill(0, 0, 0);
		text("�����Z�uP�v", 20, 530);
		text("�����Z�uO�v", 520, 530);
		text("�|���Z�uI�v", 1020, 530);
		text("����Z�uU�v", 1520, 530);
		fill(150, 170, 120);
		rect(510, 670, 870, 200);
		textSize(40);
		fill(255, 255, 255);
		text("����Փx���[�h/�uY�v�����Z  �uT�v�����Z", 510, 810);
	}
	void MATH::anser1() {
		/*�l�����Z[�ő�3��+3��](�Z+�Z)*/
		if (!anser1Generated) {
			Ma = 0, Mb = 0;
			Ma = random() % 101;
			Mb = random() % 101;
			Manser = Ma + Mb;
			anser1Generated = true;
		}
		fill(255, 255, 255);
		clear(0, 0, 64);
		textSize(80);
		text("��������͂��Ă��������BSPACE�Ŋm��B", 20, 200);
		text("���񓚂���͂��Ȃ��ƃ��j���[�ɖ߂�܂���", 20, 700);
		fill(255, 255, 0);
		text(Ma, 620, 100);
		text("+", 730, 100);
		text(Mb, 840, 100);
		text("=", 950, 100);
		text("�H", 1060, 100);
	}
	void MATH::anser2() {
		/*�l�����Z[�ő�3��-3��](�Z-�Z)*/
		if (!anser2Generated) {
			Mc = random() % 101;
			Md = random() % 101;
			if (Mc > Md) {
				Manser2 = Mc - Md;
			}
			else if (Mc < Md) {
				Manser2 = Md - Mc;
			}
			anser2Generated = true;
		}
		clear(0, 0, 64);
		textSize(80);
		text("��������͂��Ă��������BSPACE�Ŋm��B", 20, 200);
		text("���񓚂���͂��Ȃ��ƃ��j���[�ɖ߂�܂���", 20, 700);
		if (Mc > Md) {
			fill(255, 255, 0);
			text(Mc, 620, 100);
			text("-", 730, 100);
			text(Md, 840, 100);
			text("=", 950, 100);
			text("�H", 1060, 100);
		}
		else if (Mc < Md) {
			fill(255, 255, 0);
			text(Md, 620, 100);
			text("-", 730, 100);
			text(Mc, 840, 100);
			text("=", 950, 100);
			text("�H", 1060, 100);
		}
	}
	void MATH::anser3() {
		/*�l�����Z[�ő�2���~2��](�Z�~�Z)*/
		if (!anser3Generated) {
			Me = random() % 100;
			Mf = random() % 100;
			Manser3 = Me * Mf;
			anser3Generated = true;
		}
		clear(0, 0, 64);
		textSize(80);
		text("��������͂��Ă��������BSPACE�Ŋm��B", 20, 200);
		text("���񓚂���͂��Ȃ��ƃ��j���[�ɖ߂�܂���", 20, 700);
		fill(255, 255, 0);
		text(Me, 620, 100);
		text("�~", 730, 100);
		text(Mf, 840, 100);
		text("=", 950, 100);
		text("�H", 1060, 100);
	}
	void MATH::anser4() {
		/*�l�����Z[�ő�2����2��](�Z���Z)*/
		if (!anser4Generated) {
			Mg = random() % 100;
			Mh = random() % 100;
			Manser4 = Mg / Mh;
			anser4Generated = true;
		}
		clear(0, 0, 64);
		textSize(60);
		text("��������͂��Ă�������(���݂̂ŉ�)�BSPACE�Ŋm��B", 20, 200);
		textSize(80);
		text("���񓚂���͂��Ȃ��ƃ��j���[�ɖ߂�܂���", 20, 700);
		fill(255, 255, 0);
		text(Mg, 620, 100);
		text("��", 730, 100);
		text(Mh, 840, 100);
		text("=", 950, 100);
		text("�H", 1060, 100);
	}
	void MATH::anser5() {
		/*�l�����Z[�ő�4��+4��](�Z+�Z)*/
		if (!anser5Generated) {
			Mi = random() % 1101;
			Mj = random() % 1101;
			Manser5 = Mi + Mj;
			anser5Generated = true;
		}
		clear(0, 0, 64);
		textSize(80);
		text("��������͂��Ă��������BSPACE�Ŋm��B", 20, 200);
		text("���񓚂���͂��Ȃ��ƃ��j���[�ɖ߂�܂���", 20, 700);
		textSize(60);
		fill(255, 255, 0);
		text(Mi, 620, 100);
		text("�{", 730, 100);
		text(Mj, 810, 100);
		text("=", 950, 100);
		text("�H", 1060, 100);
	}
	void MATH::anser6() {
		/*�l�����Z[�ő�4��-4��](�Z-�Z)*/
		if (!anser6Generated) {
			Mk = random() % 2001;
			Ml = random() % 2001;
			if (Mk > Ml) {
				Manser6 = Mk - Ml;
			}
			else if (Mk < Ml) {
				Manser6 = Ml - Mk;
			}
			anser6Generated = true;
		}
		clear(0, 0, 64);
		textSize(80);
		text("��������͂��Ă��������BSPACE�Ŋm��B", 20, 200);
		text("���񓚂���͂��Ȃ��ƃ��j���[�ɖ߂�܂���", 20, 700);
		if (Mk > Ml) {
			fill(255, 255, 0);
			text(Mk, 570, 100);
			text("-", 730, 100);
			text(Ml, 780, 100);
			text("=", 950, 100);
			text("�H", 1060, 100);
		}
		else if (Mk < Ml) {
			fill(255, 255, 0);
			text(Ml, 570, 100);
			text("-", 730, 100);
			text(Mk, 780, 100);
			text("=", 950, 100);
			text("�H", 1060, 100);
		}
	}

	void MATH::data() {

	}

	MATH* MATH::math1()
	{
		static MATH mathInstance1;
		return &mathInstance1;
	}
	MATH* MATH::math2()
	{
		static MATH mathInstance2;
		return &mathInstance2;
	}
	MATH* MATH::math3()
	{
		static MATH mathInstance3;
		return &mathInstance3;
	}
	MATH* MATH::math4()
	{
		static MATH mathInstance4;
		return &mathInstance4;
	}
	MATH* MATH::math5()
	{
		static MATH mathInstance5;
		return &mathInstance5;
	}
	MATH* MATH::math6()
	{
		static MATH mathInstance6;
		return &mathInstance6;
	}
	void MATH::proc() {
		GAME01::getInput2();
		if (select1 == 0) {
			game();
			if (isTrigger(KEY_P)) {
				math1();
				select1 = 1;
			}
			if (isTrigger(KEY_O)) {
				math2();
				select1 = 2;
			}
			if (isTrigger(KEY_I)) {
				math3();
				select1 = 3;
			}
			if (isTrigger(KEY_U)) {
				math4();
				select1 = 4;
			}
			if (isTrigger(KEY_Y)) {
				math5();
				select1 = 5;
			}
			if (isTrigger(KEY_T)) {
				math6();
				select1 = 6;
			}
			if (isTrigger(KEY_ENTER) && !answerChecked) {
				select1 = 0;
			}
		}
		else if (select1 == 1) {
			MATH* m1 = MATH::math1();
			m1->anser1();
			key();
			if (!answerChecked) {
				if (isTrigger(KEY_SPACE)) {
					if (inputStrA[0] != '\0') {
						valueA = atoi(inputStrA);
						textSize(50);
						answerCorrect = (m1->Manser == valueA);
						answerChecked = true;
					}
				}
			}
			else {
				// ����ς� �� ���ʕ\��
				if (answerCorrect) {
					text("�����I", 700, 400);
					text("Enter�Ŏ��̖���", 700, 500);
					text("Shift�Ń��j���[�ɖ߂�", 700, 600);
				}
				else {
					text("�s�����I", 700, 400);
					text("Shift�Ń��j���[�ɖ߂�", 700, 500);
				}

				if (isTrigger(KEY_ENTER)) { //����
					MATH::math1()->anser1Generated = false;
					inputLenA = 0;
					inputStrA[0] = '\0';
					answerChecked = false;
					answerCorrect = false;
				}
				if (isTrigger(KEY_SHIFT)) { //�s����
					inputLenA = 0;
					inputStrA[0] = '\0';
					answerChecked = false;
					answerCorrect = false;
					select1 = 0;
				}
			}
		}
		else if (select1 == 2) {
			MATH* m2 = MATH::math2();
			m2->anser2();
			key();
			if (!answerChecked) {
				if (isTrigger(KEY_SPACE)) {
					if (inputStrA[0] != '\0') {
						valueA = atoi(inputStrA);
						textSize(50);
						answerCorrect = (m2->Manser2 == valueA);
						answerChecked = true;
					}
				}
			}
			else {
				// ����ς� �� ���ʕ\��
				if (answerCorrect) {
					text("�����I", 700, 400);
					text("Enter�Ŏ��̖���", 700, 500);
					text("Shift�Ń��j���[�ɖ߂�", 700, 600);
				}
				else {
					text("�s�����I", 700, 400);
					text("Shift�Ń��j���[�ɖ߂�", 700, 500);
				}

				if (isTrigger(KEY_ENTER)) { //����
					MATH::math2()->anser2Generated = false;
					inputLenA = 0;
					inputStrA[0] = '\0';
					answerChecked = false;
					anser2Generated = false;  // ���� anser2 �ŐV��萶��
				}
				if (isTrigger(KEY_SHIFT)) { //�s����
					inputLenA = 0;
					inputStrA[0] = '\0';
					answerChecked = false;
					answerCorrect = false;
					select1 = 0;
				}
			}
		}
		else if (select1 == 3) {
			MATH* m3 = MATH::math3();
			m3->anser3();
			key();
			if (!answerChecked) {
				if (isTrigger(KEY_SPACE)) {
					if (inputStrA[0] != '\0') {
						valueA = atoi(inputStrA);
						textSize(50);
						answerCorrect = (m3->Manser3 == valueA);
						answerChecked = true;
					}
				}
			}
			else {
				// ����ς� �� ���ʕ\��
				if (answerCorrect) {
					text("�����I", 700, 400);
					text("Enter�Ŏ��̖���", 700, 500);
					text("Shift�Ń��j���[�ɖ߂�", 700, 600);
				}
				else {
					text("�s�����I", 700, 400);
					text("Shift�Ń��j���[�ɖ߂�", 700, 500);
				}

				if (isTrigger(KEY_ENTER)) { //����
					MATH::math3()->anser3Generated = false;
					inputLenA = 0;
					inputStrA[0] = '\0';
					answerChecked = false;
					anser3Generated = false;  // ���� anser3 �ŐV��萶��
				}
				if (isTrigger(KEY_SHIFT)) { //�s����
					inputLenA = 0;
					inputStrA[0] = '\0';
					answerChecked = false;
					answerCorrect = false;
					select1 = 0;
				}
			}
			}
		else if (select1 == 4) {
			MATH* m4 = MATH::math4();
			m4->anser4();
			key();
			if (!answerChecked) {
				if (isTrigger(KEY_SPACE)) {
					if (inputStrA[0] != '\0') {
						valueA = atoi(inputStrA);
						textSize(50);
						answerCorrect = (m4->Manser4 == valueA);
						answerChecked = true;
					}
				}
			}
			else {
				// ����ς� �� ���ʕ\��
				if (answerCorrect) {
					text("�����I", 700, 400);
					text("Enter�Ŏ��̖���", 700, 500);
					text("Shift�Ń��j���[�ɖ߂�", 700, 600);
				}
				else {
					text("�s�����I", 700, 400);
					text("Shift�Ń��j���[�ɖ߂�", 700, 500);
				}
				if (isTrigger(KEY_ENTER)) { //����
					MATH::math4()->anser4Generated = false;
					inputLenA = 0;
					inputStrA[0] = '\0';
					answerChecked = false;
					anser4Generated = false;  // ���� anser4 �ŐV��萶��
				}
				if (isTrigger(KEY_SHIFT)) { //�s����
					inputLenA = 0;
					inputStrA[0] = '\0';
					answerChecked = false;
					answerCorrect = false;
					select1 = 0;
				}
			}
		}
		else if (select1 == 5) {
			MATH* m5 = MATH::math5();
			m5->anser5();
			key();
			if (!answerChecked) {
				if (isTrigger(KEY_SPACE)) {
					if (inputStrA[0] != '\0') {
						valueA = atoi(inputStrA);
						textSize(50);
						answerCorrect = (m5->Manser5 == valueA);
						answerChecked = true;
					}
				}
			}
			else {
				// ����ς� �� ���ʕ\��
				if (answerCorrect) {
					text("�����I", 700, 400);
					text("Enter�Ŏ��̖���", 700, 500);
					text("Shift�Ń��j���[�ɖ߂�", 700, 600);
				}
				else {
					text("�s�����I", 700, 400);
					text("Shift�Ń��j���[�ɖ߂�", 700, 500);
				}
				if (isTrigger(KEY_ENTER)) { //����
					MATH::math5()->anser5Generated = false;
					inputLenA = 0;
					inputStrA[0] = '\0';
					answerChecked = false;
					anser5Generated = false;  // ���� anser5 �ŐV��萶��
				}
				if (isTrigger(KEY_SHIFT)) { //�s����
					inputLenA = 0;
					inputStrA[0] = '\0';
					answerChecked = false;
					answerCorrect = false;
					select1 = 0;
				}
			}
		}
		else if (select1 == 6) {
			MATH* m6 = MATH::math6();
			m6->anser6();
			key();
			if (!answerChecked) {
				if (isTrigger(KEY_SPACE)) {
					if (inputStrA[0] != '\0') {
						valueA = atoi(inputStrA);
						textSize(50);
						answerCorrect = (m6->Manser6 == valueA);
						answerChecked = true;
					}
				}
			}
			else {
				// ����ς� �� ���ʕ\��
				if (answerCorrect) {
					text("�����I", 700, 400);
					text("Enter�Ŏ��̖���", 700, 500);
					text("Shift�Ń��j���[�ɖ߂�", 700, 600);
				}
				else {
					text("�s�����I", 700, 400);
					text("Shift�Ń��j���[�ɖ߂�", 700, 500);
				}

				if (isTrigger(KEY_ENTER)) { //����
					MATH::math6()->anser6Generated = false;
					inputLenA = 0;
					inputStrA[0] = '\0';
					answerChecked = false;
					anser6Generated = false;  // ���� anser2 �ŐV��萶��
				}
				if (isTrigger(KEY_SHIFT)) { //�s����
					inputLenA = 0;
					inputStrA[0] = '\0';
					answerChecked = false;
					answerCorrect = false;
					select1 = 0;
				}
			}
			}
		textSize(80);
		fill(255, 255, 255);
		text(inputStrA, 200, 300);  // ������\��
		fill(255, 255, 255);
	}
	void MATH::key() {
		if (inputLenA < 31) {
			if (isTrigger2(KEY_0)) { inputStrA[inputLenA++] = '0'; }
			else if (isTrigger2(KEY_1)) { inputStrA[inputLenA++] = '1'; }
			else if (isTrigger2(KEY_2)) { inputStrA[inputLenA++] = '2'; }
			else if (isTrigger2(KEY_3)) { inputStrA[inputLenA++] = '3'; }
			else if (isTrigger2(KEY_4)) { inputStrA[inputLenA++] = '4'; }
			else if (isTrigger2(KEY_5)) { inputStrA[inputLenA++] = '5'; }
			else if (isTrigger2(KEY_6)) { inputStrA[inputLenA++] = '6'; }
			else if (isTrigger2(KEY_7)) { inputStrA[inputLenA++] = '7'; }
			else if (isTrigger2(KEY_8)) { inputStrA[inputLenA++] = '8'; }
			else if (isTrigger2(KEY_9)) { inputStrA[inputLenA++] = '9'; }
			inputStrA[inputLenA] = '\0'; // ������I�[
		}
	}
};

