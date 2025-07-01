#include "../../libOne/inc/libOne.h"
#include "input2.h"

namespace GAME01 {

	static short InputState2[2][INPUT2_CODE_NUM];
	static int Now2 = 1;

	void initInput2() {
		for (int i = 0; i < INPUT2_CODE_NUM; i++) {
			InputState2[Now2][i] = 0;
			InputState2[!Now2][i] = 0;
		}
	}
	void getInputState2() {

		Now2 = !Now2;

		//キーボード
		InputState2[Now2][KEY_1] = GetAsyncKeyState('1');
		InputState2[Now2][KEY_2] = GetAsyncKeyState('2');
		InputState2[Now2][KEY_3] = GetAsyncKeyState('3');
		InputState2[Now2][KEY_4] = GetAsyncKeyState('4');
		InputState2[Now2][KEY_5] = GetAsyncKeyState('5');
		InputState2[Now2][KEY_6] = GetAsyncKeyState('6');
		InputState2[Now2][KEY_7] = GetAsyncKeyState('7');
		InputState2[Now2][KEY_8] = GetAsyncKeyState('8');
		InputState2[Now2][KEY_9] = GetAsyncKeyState('9');
		InputState2[Now2][KEY_0] = GetAsyncKeyState('0');
	}
	void getInput2() {
		getInputState2();
	}
	int isPress2(INPUT2_CODE inCode) {
		return InputState2[Now2][inCode];
	}
	int isTrigger2(INPUT2_CODE inCode) {
		if (InputState2[!Now2][inCode] == 0 && InputState2[Now2][inCode]) {
			return 1;
		}
		return 0;
	}
}
