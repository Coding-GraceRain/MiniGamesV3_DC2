#include "KEYCONFIG.h"
#include "GAME09.h"
#include "CONTAINER.h"
#include "../../libOne/inc/graphic.h"
#include "../../libOne/inc/input.h"
#include <algorithm>

namespace GAME09 {
	KEYCONFIG::KEYCONFIG(GAME* game) :
		GAME_OBJECT(game) {
	}

	KEYCONFIG::~KEYCONFIG() {

	}

	void KEYCONFIG::create() {
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 6; j++) {
				KeyConfig[i][j] = KC_MAINSUB();
			}
		}
		KeyConfig[0][0].main = KEY_A;
		KeyConfig[0][1].main = KEY_S;
		KeyConfig[0][2].main = KEY_C;
		KeyConfig[0][3].main = KEY_N;
		KeyConfig[0][4].main = KEY_K;
		KeyConfig[0][5].main = KEY_L;
		KeyConfig[1][0].main = KEY_A;
		KeyConfig[1][1].main = KEY_S;
		KeyConfig[1][2].main = KEY_C;
		KeyConfig[1][2].sub  = KEY_N;
		KeyConfig[1][3].main = KEY_K;
		KeyConfig[1][4].main = KEY_L;
		KeyConfig[2][0].main = KEY_S;
		KeyConfig[2][1].main = KEY_C;
		KeyConfig[2][2].main = KEY_N;
		KeyConfig[2][3].main = KEY_K;
		KeyConfig[3][0].main = KEY_S;
		KeyConfig[3][1].main = KEY_C;
		KeyConfig[3][1].sub  = KEY_N;
		KeyConfig[3][2].main = KEY_K;
		KeyConfig[4][0].main = KEY_C;
		KeyConfig[4][1].main = KEY_N;
		KeyConfig[5][0].main = KEY_C;
		KeyConfig[5][0].sub  = KEY_N;

		SetTriggers();
	}

	void KEYCONFIG::SetTriggers() {
		Triggers.clear();
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 6; j++) {
				bool main = false;
				do {
					main = !main;
					INPUT_CODE k = main ? KeyConfig[i][j].main : KeyConfig[i][j].sub;
					if (k != KEY_NONE) {
						bool exist = false;
						for (auto it = Triggers.begin(); it != Triggers.end(); it++) {
							if (it->Key == k) {
								exist = true;
								break;
							}
						}
						if (!exist) Triggers.emplace_back(KEY_TRIGGER{ k,false,false });
					}
				} while (main);
			}
		}
	}

	void KEYCONFIG::init() {
		
	}

	void KEYCONFIG::update() {
		for (auto it = Triggers.begin(); it != Triggers.end(); it++) {
			it->trigger = isTrigger(it->Key);
			it->press = isPress(it->Key);
		}
	}

	void KEYCONFIG::draw() {
		
	}

	KC_MAINSUB KEYCONFIG::getKeyConfig(int numLane, int lane){
		return KeyConfig[6 - numLane][lane];
	}

	bool KEYCONFIG::keyTrigger(INPUT_CODE key){
		for (auto it = Triggers.begin(); it != Triggers.end(); it++) {
			if (it->Key == key) {
				return it->trigger;
			}
		}
		return false;
	}
	bool KEYCONFIG::keyPress(INPUT_CODE key){
		for (auto it = Triggers.begin(); it != Triggers.end(); it++) {
			if (it->Key == key) {
				return it->press;
			}
		}
		return false;
	}
	void KEYCONFIG::setTrigger(INPUT_CODE key, bool value){
		for (auto it = Triggers.begin(); it != Triggers.end(); it++) {
			if (it->Key == key) {
				it->trigger = value;
				return;
			}
		}
	}
}