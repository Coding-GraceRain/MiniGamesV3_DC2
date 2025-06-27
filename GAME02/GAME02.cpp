#include "../../libOne/inc/libOne.h"
#include "../MAIN/MAIN.h"
#include "GAME02.h"
//#include<stdlib.h>
#include <time.h>
extern bool EscapeKeyValid;
namespace GAME02{
	const int cardall = 13;
	int cardimg[cardall];
	int a;
	//�Q�[����
	int gamest = 0;
	int maingame = 0;
	int BGM = 0;
	//�f�B�[���[
	int GDE = 0;
	int randDE1 = 0;
	int randDE2 = 0;
	int randDE3 = 0;
	int randDE4 = 0;
	int randDE5 = 0;
	//����
	int GME = 0;
	int randME1 = 0;
	int randME2 = 0;
	int randME3 = 0;
	int randME4 = 0;
	int randME5 = 0;
	//�J�E���g
	int Hitcount = 0;
	int Scount = 0;
	int re = 0;

	int GAME::create() {
		BGM = 0;
		/*for (int i = 0; i < cardall; i++) {
			//char filename[64];
			//sprintf_s(filename, "../MAIN/assets/game02/%d.png", i + 1);
		}*/
		//�J�[�h�̉摜���[�h
		    cardimg[0] = loadImage("..\\MAIN\\assets\\game02\\0.png");
			cardimg[1] = loadImage("..\\MAIN\\assets\\game02\\1.png");
			cardimg[2] = loadImage("..\\MAIN\\assets\\game02\\2.png");
			cardimg[3] = loadImage("..\\MAIN\\assets\\game02\\3.png");
			cardimg[4] = loadImage("..\\MAIN\\assets\\game02\\4.png");
			cardimg[5] = loadImage("..\\MAIN\\assets\\game02\\5.png");
			cardimg[6] = loadImage("..\\MAIN\\assets\\game02\\6.png");
			cardimg[7] = loadImage("..\\MAIN\\assets\\game02\\7.png");
			cardimg[8] = loadImage("..\\MAIN\\assets\\game02\\8.png");
			cardimg[9] = loadImage("..\\MAIN\\assets\\game02\\9.png");
			cardimg[10] = loadImage("..\\MAIN\\assets\\game02\\10.png");
			cardimg[11] = loadImage("..\\MAIN\\assets\\game02\\11.png");
			cardimg[12] = loadImage("..\\MAIN\\assets\\game02\\12.png");
			cardimg[13] = loadImage("..\\MAIN\\assets\\game02\\13.png");
		//���C�����[�v���ł�ESC�L�[�ł̏I������𖳌�������
		EscapeKeyValid = false;
		//�����ɂ̓Q�[���J�n����1�񂾂��s�����̂��L�q����
		textSize(200);
		return 0;
	}
	void GAME::destroy(){
		//���C�����[�v���ł�ESC�L�[�ł̏I�������L��������
		EscapeKeyValid = true;
		//�����ɂ̓Q�[���I������1�񂾂��s�����̂��L�q����
		stopSound(loadSound("..\\MAIN\\assets\\game02\\BGM.wav"));
		gamest = 0;
		reset();
	}
	void GAME::reset() {
		GDE = 0;
		GME = 0;
		Scount = 0;
		Hitcount = 0;
		randDE1 = 0;
		randDE2 = 0;
		randDE3 = 0;
		randDE4 = 0;
		randME1 = 0;
		randME2 = 0;
		randME3 = 0;
		randME4 = 0;
		randME5 = 0;
		maingame = 0;
		re = 0;
	}
	void GAME::proc() {
		//BGMon
		if (BGM == 0) {
			playSound(loadSound("..\\MAIN\\assets\\game02\\BGM.wav"));
			BGM = 1;
		}
		if (gamest == 0) {
			//�^�C�g��
			clear(0, 0, 64);
			textSize(150);
			text("�u���b�N�W���b�N", 200, 200);
			textSize(110);
			text("�X�y�[�X�L�[�������ăX�^�[�g", 200, 900);
			text("���v21����낤�I", 550, 600);
			if (isTrigger(KEY_SPACE)) {
				//�Q�[���ɓ���
				gamest = 1;
			}
		}
		if (gamest != 0) {
			/*
			clear(0, 0, 64);
			if (isTrigger(KEY_ENTER)) {
				//��D
				/*for (int i = 0; i < 9; i++) {
					//�����_���Ȑ�������
					srand(time(0));
					randDE[i] = rand() % 13;
					randME[i] = rand() % 13;
					//���߂�ꂽ�������摜�Ăяo���ɂ����
					DEimg[i] = randDE[i];
					MEimg[i] = randME[i];
					//11�ȏ��10��
					if (randDE[i] >= 11) {
						randDE[i] = 10;
					}
					if (randME[i] >= 11) {
						randME[i] = 10;
					}
					//�����̐��l�i�݌v�j�������
					for (int j = i + 1; j < 9; j++) {
						GDE[j] += randDE[i];
						GME[j] += randME[i];
					}
					if (GDE[i] > 21) {
						Dcard = i;
					}
					if (GME[i] > 21) {
						Mcard = i;
					}
					for (int i = 0; i < Dcard; i++) {
						DF = i;
					}
					for (int i = 0; i < Mcard; i++) {
						MF = i;
					}
				}
			}
			*/
			srand(time(0));
			if (maingame != 100) {
				//�f�B�[���[�Ǝ�����1�A2���ڏ���
				randDE1 = rand() % 10 + 1;
				GDE += randDE1;
				randDE2 = rand() % 10 + 1;
				GDE += randDE2;
				randME1 = rand() % 10 + 1;
				GME += randME1;
				randME2 = rand() % 10 + 1;
				GME += randME2;
				maingame = 100;
			}
			clear(0, 0, 64);
			//�f�B�[���[�J�[�h����
			image(cardimg[randDE1], 100, 50);
			image(cardimg[randDE2], 200, 50);
			image(cardimg[randDE3], 300, 50);
			image(cardimg[randDE4], 400, 50);
			//�����J�[�h����
			image(cardimg[randME1], 900, 50);
			image(cardimg[randME2], 1000, 50);
			image(cardimg[randME3], 1100, 50);
			image(cardimg[randME4], 1200, 50);
			image(cardimg[randME5], 1300, 50);
			text("�f�B�[���[�̐�", 100, 600);
			text(GDE, 100, 650);
			text("�����̐�", 1000, 600);
			text(GME, 1000, 650);
			if (Scount == 0) {
				text("�q�b�g�Ȃ�����L�[�㥃X�^���h�Ȃ�����L�[��", 850, 900);
				text("�f�B�[���[�̐�", 100, 600);
				text(GDE, 100, 650);
				text("�����̐�", 1000, 600);
				text(GME, 1000, 650);
			}
			//�q�b�g
			if (isTrigger(KEY_UP)) {
				if (Hitcount == 0) {
					randME3 = rand() % 10 + 1;
					GME += randME3;
				}
				if (Hitcount == 1) {
					randME4 = rand() % 10 + 1;
					GME += randME4;
				}
				if (Hitcount == 2) {
					randME5 = rand() % 10 + 1;
					GME += randME5;
				}
				Hitcount++;
			}
			//�u���b�N�W���b�N�Ȃ瑦����
			if (GME == 21) {
				Scount = 5;
				re = 1;
			}
			//�X�^���h
			if (isTrigger(KEY_DOWN)) {
				re = 1;
				if (GDE <= 18) {
					randDE3 = rand() % 10 + 1;
					GDE += randDE3;
				}
				if (GDE <= 18) {
					randDE4 = rand() % 10 + 1;
					GDE += randDE4;
				}
				//��������
				if (GDE > GME && GDE <= 21) {
					Scount = 3;
				}
				if (GDE < GME && GME <= 21) {
					Scount = 4;
				}
				if (GDE > 21) {
					Scount = 2;
				}
				if (GME > 21) {
					Scount = 1;
				}
				if (GDE > 21 && GME > 21) {
					Scount = 6;
				}
				if (GDE == GME) {
					Scount = 6;
				}
				if (GDE == 21 && (GME != 21 && GME >21)) {
					Scount = 7;
				}
			}
			switch (Scount) {
			case 1:
				textSize(110);
				text("�o�X�g�I", 750, 800);
				text("YOU LOSE", 700, 900);
				break;
			case 2:
				textSize(110);
				text("�f�B�[���[���o�X�g�I", 280, 800);
				text("YOU WIN!", 700, 900);
				break;
			case 3:
				textSize(110);
				text("YOU LOSE", 700, 900);
				break;
			case 4:
				textSize(110);
				text("YOU WIN!", 700, 900);
				break;
			case 5:
				textSize(110);
				text("�u���b�N�W���b�N�I�I�I�I�I", 200, 800);
				text("VICTORY!!!!", 680, 900);
				break;
			case 6:
				textSize(110);
				text("DRAW", 700, 900);
				break;
			case 7:
				textSize(110);
				text("�f�B�[���[���u���b�N�W���b�N�I�I�I�I�I", 150, 800);
				text("YOU LOSE...", 680, 900);
			}
			//���Z�b�g
			if (re == 1) {
				textSize(50);
				text("R�L�[�Ń��X�^�[�g", 1500, 1080);
				if (isTrigger(KEY_R)) {
					reset();
				}
			}
		}
		fill(255);
		textSize(50);
		text("ESC�L�[�Ń��j���[�ɖ߂�", 0, 1080);
		if (isTrigger(KEY_ESCAPE)) {
			main()->backToMenu();
			//stopSound(loadSound("..\\MAIN\\assets\\game02\\BGM.wav"));
		}
	}
}
