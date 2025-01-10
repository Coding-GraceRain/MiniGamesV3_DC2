#include "../../libOne/inc/libOne.h"
#include"GAME03.h"
#include"CONTAINER.h"
#include"FADE.h"
#include"MAP.h"
#include"CHARACTER_MANAGER.h"
#include "STAGE.h"
#include<time.h>

namespace GAME03 {
	void STAGE::create() {
		Stage = game()->container()->data().stage;
	}
	void STAGE::init() {
		Stage.backToTitleTime = game()->container()->data().stage.backToTitleTime;
		game()->map()->init();
		game()->characterManager()->init();
		game()->fade()->inTrigger();
		time(&Stage.s_time);
		time(&Stage.n_time);
		loopBgm = true;
		op_option = false;
		flg_clear = false;
	}
	void STAGE::update() {
		game()->characterManager()->update();
		game()->map()->update();
	}
	void STAGE::draw() {
		if (loopBgm) {
			//playLoopSound(game()->container()->data().volume.Snd_B);
			loopBgm = false;
		}
		BackGround();
		game()->map()->draw();
		game()->characterManager()->draw();
		if (game()->characterManager()->player()->died()) {
			Logo(Stage.gameOverImg, Stage.gameOverColor);
		}
		else if (game()->characterManager()->player()->survived()) {
			Logo(Stage.stageClearImg, Stage.stageClearColor);
		}
		else {
			if (isTrigger(KEY_ESCAPE)) {
				Stage.time = Stage.stp_time;
				op_option = true;
			}
			if (op_option) {
				time(&Stage.cnt_time);
				image(Stage.playStopImg, 0, 0);
				if (isTrigger(KEY_N)) {
					Stage.s_time += (Stage.cnt_time - Stage.n_time);
					op_option = false;
				}
				if (isTrigger(KEY_O)) {
					game()->fade()->outTrigger();
				}
			}
			else {
				time(&Stage.n_time);
				Stage.time = Stage.n_time - Stage.s_time;
				Stage.stp_time = Stage.time;
			}
			if (Stage.time >= 30) {
				flg_clear = true;
			}
			fill(225);
			textSize(90);
			text((let)(int)Stage.time, width / 2.0f, height / 10.0f);
		}
		fill(0);
		game()->fade()->draw();
	}
	void STAGE::BackGround() const {
		clear();
		rectMode(CORNER);
		imageColor(Stage.backColor);
		image(Stage.backImg, 0, 0);
	}
	void STAGE::Logo(int img, const COLOR& color) {
		imageColor(color);
		image(img, Stage.logoPx, Stage.logoPy);
		Stage.backToTitleTime -= delta;
	}
	void STAGE::nextScene() {
		if (Stage.backToTitleTime <= 0) {
			//stopSound(game()->container()->data().volume.Snd_B);
			game()->fade()->outTrigger();
		}
		if (game()->fade()->outEndFlag()) {
			game()->setCurScene(game()->title());
		}
	}
}
