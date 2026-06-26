#pragma once

namespace GAME00 { //šGAMExx‚Í©•ª‚Ì”Ô†‚É‡‚í‚¹‚é–!!
	enum INPUT2_CODE {
		KEY_1,
		KEY_2,
		KEY_3,
		KEY_4,
		KEY_5,
		KEY_6,
		KEY_7,
		KEY_8,
		KEY_9,
		KEY_0,
		INPUT2_CODE_NUM
	};
	void initInput2();
	void getInput2();
	void getInputState2();
	int isPress2(INPUT2_CODE inCode);
	int isTrigger2(INPUT2_CODE inCode);

}
