#include "../../libOne/inc/libOne.h"
#include "../MAIN/MAIN.h"
#include "GAME15.h"

//���C�����[�v����ESC�L�[�̔�������邵�Ȃ��̏�Ԃ�ێ�����O���[�o���ϐ�
extern bool EscapeKeyValid;

namespace GAME15
{
	int GAME::create()
	{
		//���C�����[�v���ł�ESC�L�[�ł̏I������𖳌�������
		EscapeKeyValid = false;

		//�����ɂ̓Q�[���J�n����1�񂾂��s�����̂��L�q����



		return 0;
	}

	void GAME::destroy()
	{
		//�����ɂ̓Q�[���I������1�񂾂��s�����̂��L�q����



		//���C�����[�v���ł�ESC�L�[�ł̏I�������L��������
		EscapeKeyValid = true;
	}

	void GAME::proc()
	{
		clear(0, 0, 64);

		print(delta);

		fill(255);
		text("ESC�L�[�Ń��j���[�ɖ߂�", 0, 1080);
		if (isTrigger(KEY_ESCAPE)) {
			main()->backToMenu();
		}
	}
}
