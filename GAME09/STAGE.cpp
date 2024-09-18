#include "GAME09.h"
#include "STAGE.h"
#include "CONTAINER.h"
//#include "RHYTHM_GAME_CONTROLLER.h"
#include "../../libOne/inc/input.h"
#include "../../libOne/inc/graphic.h"
//#include "textFunc.h"

namespace GAME09 {
	STAGE::STAGE(class GAME* game) :
		SCENE(game) {

	}
	STAGE::~STAGE() {

	}
	void STAGE::create() {
		Stage = game()->container()->data().stage;
	}
	void STAGE::init() {
		//game()->rgCont()->init();
		//Pause = false;
		Choices = RETRY;
	}
	void STAGE::update() {
		//if (Pause) {
		//	if (game()->fade()->inEndFlag()) {
		//		if (isTrigger(KEY_UP) && Choices > 0) Choices = (CHOICES)(Choices - 1);
		//		if (isTrigger(KEY_DOWN) && Choices < NUM_CHOICES - 1) Choices = (CHOICES)(Choices + 1);
		//	}
		//}
		//else {
		//	if (game()->rgCont()->isPlay() && isTrigger(KEY_ESCAPE)) {
		//		Pause = true;
		//		game()->rgCont()->soundMNG()->stopMusic();
		//	}
		//	else {
		//		game()->rgCont()->update();
		//	}
		//}
	}
	void STAGE::draw() {
		clear(255);
		//game()->back()->draw(game()->rgCont()->getSongInfo().backImageIdx, game()->rgCont()->getSongInfo().backImageSize);
		//game()->rgCont()->draw();
		//if (Pause) {
		//	fill(Stage.pauseBackColor);
		//	rectMode(CENTER);
		//	rect(width / 2, height / 2, width, height);
		//	fill(255);
		//	textfMode(M_CENTER);
		//	textf("PAUSE", Stage.pauseStrPos, Stage.pauseStrSize);
		//	VECTOR2 pos = Stage.choicesFirstPos;
		//	for (int i = 0; i < NUM_CHOICES; i++) {
		//		if (i == Choices) {
		//			fill(255, 0, 0);
		//		}
		//		else {
		//			fill(255);
		//		}
		//		textf(Stage.choicesStr[i], pos, Stage.choicesSize);
		//		pos += Stage.choicesNextOfst;
		//	}
		//}
	}
	void STAGE::nextScene() {
		//if (game()->rgCont()->isChangeScene()) {
		//	game()->fade()->outStart();
		//}
		//if (Pause && isTrigger(KEY_ENTER)) {
		//	game()->fade()->outStart();
		//}
		//if (game()->fade()->outEndFlag()) {
		//	if (Pause) {
		//		switch (Choices)
		//		{
		//		case RETRY:
		//			game()->changeScene(GAME::STAGE_ID);
		//			break;
		//		case SELECT:
		//			game()->changeScene(GAME::SELECT_ID);
		//			break;
		//		default:
		//			break;
		//		}
		//	}
		//	else {
		//		game()->rgCont()->judgeMNG()->resetCombo();
		//		game()->changeScene(GAME::GAME_CLEAR_ID);
		//	}
		//}
	}
}