#include "../../libOne/inc/libOne.h"
#include "../MAIN/MAIN.h"
#include "GAME01.h"
#include "time.h"
#include"math.h"
namespace GAME01
{
	int GAME::create()  //1�����
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
		//���v���C�񐔃J�E���g
		c2++;
		// ���ʂ��t�@�C���ɏ�������
		if (fopen_s(&file2, "playcount.txt", "w") == 0) {
			fprintf_s(file2, "%d", c2);  // �V�����l���t�@�C���ɏ�������
			fclose(file2);  // �t�@�C�����
		}
	}

	void GAME::draw()
	{
		clear(0, 0, 64);
		textSize(80);
		fill(255, 255, 0);
		text("�]�g��", 820, 100);
		textSize(50);
		fill(255);
		text("ENTER�L�[�Ń��j���[�ɖ߂�", 620, 980);
		fill(0, 255, 0);
		rect(100, 200, 800, 300);
		textSize(60);
		fill(0);
		text("�l�����Z/�uM�vKEY������", 100, 380);
		textSize(30);
		fill(255);
		text("�������ԓ��Ŏl���̉��Z�����郂�[�h�ł��B���s�����ł����ɐi�߂܂��B", 900, 380);
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

